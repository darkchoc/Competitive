"""
You need to write the code for a basic running API server with an endpoint which can be used to trigger an email to a 3rd party tool like sendgrid etc., which will finally dispatch the email to the end user and return success/failure.
1. It will be POST REST API accepting 2 things in the JSON body - email id and message, both strings.
2. The response would be simply either success or failure. 
3.  The 3rd party method can be simply mocked which will actually send the email to the end user and return success/failure.
4. You can use any language of your choice and refer the official docs for syntax etc.


Part 2:
Let's scale this new API.
1. For this you need to allow array of multiple emailId + message objects instead of a single one in the POST body.
2. Instead of single 3rd party tool, allow a combination of multiple tools to dispatch the emails faster. These can still be mocked.
3. Think about what else can be done to make it more scalable, faster, future compatible.

"""

"""
Things I need to see:

1. How to send multiple email requests to a vendor in a multithreaded manner ? Thread pools ? 
2. Can it be made asynchronous? Would it make sense to make it async? If we are using thread pools, I don't think it would make sense to make email requests async.
3. How to put a timeout in place for the email request sent to vendor? Also if timeout reached, how to cancel request sent to vendor?  
4. When multiple email vendors, how to send multiple requests to each? Should there be a threadpool for each vendor? Or can we implement some job queue from where vendors can pick up messages? Or should a central coordinator assign messages to vendors? 
5. Benefit of latter approach is that central coordinator can load balance and also implement some retry mechanism for emails that failed to send by one vendor.

"""

from flask import Flask, request, jsonify
from flask_wtf import FlaskForm
from wtforms import EmailField, TextAreaField, SubmitField, FormField, FieldList
from wtforms.validators import DataRequired, Email

app = Flask(__name__)

app.config['WTF_CSRF_ENABLED'] = False # need to set this to enable form validation of FlaskForm if sending request via Postman and using FlaskForm approach. Not required for simple approach.

# PART 1

# function mocking the vendor that actually sends the email
def sendEmailVendor(email, message):
    print("Sent! email:" + email + " , message = " + message + " **** ")
    return True
        
# first simple implementation. 
@app.route('/send_email_simple', methods=['POST'])
def send_email_simple():
    request_data = request.get_json()
    email, message = request_data.get('email'), request_data.get('message')
    # requestData.get() is better than requestData['email'] as .get() returns empty in case 'email' is not present in the requestData but requestData['email'] will error out. 

    if not email or not message:
        return jsonify({'status': 'failure', 'message': 'Email and message are required'}), 400

    success = sendEmailVendor(email, message)

    if success:
        return jsonify({'status':'success'}), 200
    else:
        return jsonify({'status':'failure', 'message':'Failed to send email'}), 500

# form based approach for sending a single mail. Form based approach allows for using validators out of the box.   
class EmailForm(FlaskForm):
    email = EmailField('Email', validators=[DataRequired(), Email()])
    message = TextAreaField('Message', validators=[DataRequired()])
    submit = SubmitField('Send Message')


@app.route('/send_email_form', methods=['POST'])
def send_email_form():
    form = EmailForm()
    if form.validate_on_submit():
        email = form.email.data
        message = form.message.data
        # no need to check if email/message is present or not, as we have already validated the form.
        success = sendEmailVendor(email, message)
        if success:
            return jsonify({'status': 'success'}), 200
        else:
            return jsonify({'status': 'failure', 'message': 'Failed to send message'}), 500
    return jsonify({'status': 'failure', 'message': 'Form not validated on submit'}), 400

# PART 2.1 starts

# Simple approach for sending an array of (email, message) objects in post request.
@app.route('/send_emails_simple', methods=['POST'])
def send_emails_simple():
    request_data = request.get_json()
    email_messages = request_data.get('email_messages')

    if not email_messages or not isinstance(email_messages, list):
        return jsonify({'status': 'failure', 'message': 'email_messages must be non empty array'}), 400
    
    responses = []
    for item in email_messages:
        email = item.get('email')
        message = item.get('message')
        if not email or not message:
            responses.append({'status': 'failure', 'message': 'Email or message not present'})
        else:
            success = sendEmailVendor(email, message)
            if success:
                responses.append({'status': 'success'})
            else:
                responses.append({'status': 'failure', 'message': 'Failed to send message'})
    
    status_code = 200 if all(response.get('status')=='success' for response in responses) else 500

    return jsonify(responses), status_code


# Form based approach for sending multiple emails. We can have a nested form here. There is a submit button associated with every nested form. It's not ideal.
class EmailsForm(FlaskForm):
    email_array = FieldList(FormField(EmailForm), min_entries=1, max_entries=3)
    submit = SubmitField('Send Emails')

@app.route('/send_emails_form', methods=['POST'])
def send_emails_form():
    # pay attention to how POST request is constructed in POSTMAN. In form-data, we need to provide key value pairs like -> email_array-1-email : email1@gmail.com, email_array-1-message : This is message 1, email_array-2-email: email2@gmail.com, email_array-2-message : This is message 2. Since flask uses -_- as separator and replaces underscore with an index.

    form = EmailsForm()
    print(form.data)
    if form.validate_on_submit():
        email_messages = form.email_array.data
        # no need to check for validity of email_messages array as we have already validated form on submit.
        responses = []
        for item in email_messages:
            email = item.get('email')
            message = item.get('message')
            success = sendEmailVendor(email, message)
            if success:
                responses.append({'status':'success'})
            else:
                responses.append({'status': 'failure', 'message':'Failed to send message'})
        
        status_code = 200 if all(response.get('status')=='success' for response in responses) else 500
        return jsonify(responses), status_code
    
    return jsonify({'status': 'failure', 'message': 'Form not validated on submit'}), 400


# PART 2.2 (but keeping it single threaded at the moment)

def sendEmailVendor2(email, message):
    print("Vendor2 -> Email:" + email + " message:" + message)
    return True

def sendEmailVendor3(email, message):
    print("Vendor3 -> Email:" + email + " message:" + message)
    return True

available_third_party_tools = [sendEmailVendor, sendEmailVendor2, sendEmailVendor3]

def distribute_emails(email_messages, tools):
    # currently sending emails to tools in round robin fashion
    responses = []
    for i, email_message in enumerate(email_messages):
        email = email_message.get('email')
        message = email_message.get('message')

        if not email or not message:
            responses.append({'status':'failure', 'message': 'email or message not present'})
        else:
            success = tools[i%len(tools)](email, message)
            if success:
                responses.append({'status': 'success'})
            else:
                responses.append({'status':'failure', 'message':'Failed to send message'})
    status_code = 200 if all(response.get('status')=='success' for response in responses) else 500
    return responses, status_code

@app.route('/send_emails_tools', methods=['POST'])
def send_emails_tools():
    request_data = request.get_json()
    email_messages = request_data.get('email_messages')
    tools = request_data.get('tools')
    if not email_messages or not isinstance(email_messages, list):
        return jsonify({'status': 'failure', 'message': 'email_messages must be non empty array'}), 400
    
    if not tools:
        tools = [tool for tool in available_third_party_tools]
    elif not isinstance(tools, list):
        return jsonify({'status': 'failure', 'message': 'tools must be a non empty array'}), 400
    else:
        # important. Since we don't have a separate module where we're keeping email vendors, we have to use global. Otherwise let's say we had a module called emailVendor, then we could have used: func = getattr(emailVendor, func_name_in_string). 
        tools = [globals().get(x) for x in tools if globals().get(x) in available_third_party_tools]  
        if len(tools) == 0:
            return jsonify({'status': 'failure', 'message': 'invalid set of tools provided. Options: ' + str([tool.__name__ for tool in available_third_party_tools])}), 400
    
    return distribute_emails(email_messages, tools)


if __name__ == '__main__':
    app.run(debug=True)