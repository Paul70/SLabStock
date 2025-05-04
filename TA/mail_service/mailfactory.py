import os
import smtplib
import sys
from dotenv import load_dotenv
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from pathlib import Path


# mit ner if abfrage einfach regeln
current_directory = os.path.dirname(os.path.abspath(__file__))
print(f"Current directory: {current_directory}")
sys.path.append('/path/to/my_module')
import libpybind


class MyMailFactory(libpybind.MailFactory):

        # hier bekomme ich ein dict rein
        def createSettings(self, msg):
            return libpybind.PyMail(msg)

def send_mail(mail_subject, mail_body):
    
    load_dotenv(Path.joinpath(Path.cwd().parent.parent.parent, ".env"))

    msg = MIMEMultipart()
    msg['From'] = 'mail@paulheidenreich.com'
    #msg['To'] = 'ariane-salzmann@hotmail.de'
    msg['To'] = 'mail@paulheidenreich.com'
    msg['Subject'] = mail_subject

    msg.attach(MIMEText(mail_body, 'plain'))

    smtp_server = 'smtp.paulheidenreich.com'
    smtp_server_port = '587'
    pw = os.getenv('SMTP_KEY')

    login = 'mail@paulheidenreich.com'

    try:
        # Set up the SMTP server and login if required
        server = smtplib.SMTP(smtp_server, smtp_server_port)
        server.starttls()  # Upgrade the connection to a secure encrypted SSL/TLS connection
        
        # Log in to the server if necessary
        if login and pw:
            server.login(login, pw)
        
        # Send the email
        server.send_message(msg)
        print("Email sent successfully!")
        
    except Exception as e:
        print(f"Failed to send email: {e}")
    
    finally:
        server.quit()




def mail(): # hier bie dieser method muss dann der input rein, der aus slabstock kommt
    my_dict = {"address": "Alice", "subject": 30, "message": "New York"}
    mailfactory = MyMailFactory()    
    mail = mailfactory.createSettings(my_dict)
    print(mail.getMessage())
    #send_mail('From Paul', mail.getMessage())


    return mail


#mail()
#print(message.getMessage())

# this file has now to be called via a pyhton module loader from c++
# Concept:
# Call of create method which constructs a Mail object inside this pyhton module
# Then we call this python script from c++ which will return this Mail object into my 
# c++ code 
