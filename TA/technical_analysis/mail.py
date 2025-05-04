import os
import smtplib
from dotenv import load_dotenv
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from pathlib import Path

def send_mail(mail_subject, mail_body):
    
    load_dotenv(Path.cwd().parent)

    msg = MIMEMultipart()
    msg['From'] = 'mail@paulheidenreich.com'
    #msg['To'] = 'ariane-salzmann@hotmail.de'
    msg['To'] = 'mail@paulheidenreich.com'
    msg['Subject'] = mail_subject

    msg.attach(MIMEText(mail_body, 'plain'))

    smtp_server = 'smtp.paulheidenreich.com'
    smtp_server_port = '587'
    pw = os.getenv('SMTP_KEY')
    print(pw)

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


send_mail('From Paul', 'Hello there :)')