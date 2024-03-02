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

1. How to make the sendEmailVendor call in a way that it can timeout (and cancel request if not yet sucessful?)
2. When extending to have multiple emails and messages simultaneously, how do send multiple requests at once? -> Basically multithreading in python
3. When having multiple vendors, how to open multiple connections in a multithreaded manner. Should threadpool be for every vendor? Or should we send multiple requests to every vendor? Basically might need to do intelligent load balancing and checking that if one vendor is failing to send message, try next one.

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



if __name__ == '__main__':
    app.run(debug=True)