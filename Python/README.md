QUICK SUMMARY
When setting project from scratch on Windows:
python -m venv venv
pip install -r requirements.txt
Set-ExecutionPolicy Unrestricted -Scope Process
.\vevn\Scripts\Activate.ps1

DETAILS:

1. To create virtual environment in windows.
    -> Go to folder where you want to create python project. ("cd Python" in our case).
    -> python -m venv vevn (the second venv is the name of the virtualenv we just created).
2. To activate virtualenv, the net suggests we do: ".\venv\Scripts\activate.bat" but since in Windows, at the moment I am using powershell, .bat scripts don't work. If we try to activate via ".\venv\Scripts\Activate.ps1" we get error that running scripts in disabled. It is a good thing to disable scripts, but here we need to change the policy of powershell to allow running the script. To do this:
    -> Set-ExecutionPolicy Unrestricted -Scope Process
    This would set execution policy to Unrestricted but only for this powershell session. This is a safe way and this is how you should ALWAYS do this.
    -> Before executing the above command and after executing as well, you can check current execution policy using following command: get-ExecutionPolicy 
Once execution policy is updated, just run ".\venv\Scripts\Activate.ps1"
So in short, follow these two commands when trying to activate virtual env in a new powershell:
-> Set-ExecutionPolicy Unrestricted -Scope Process
-> .\vevn\Scripts\Activate.ps1


Your virtualenv will be activated. To deactivate, just type "deactivate".