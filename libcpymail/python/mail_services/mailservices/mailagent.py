import os
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

import utility
utility.prepare_slabstock_module_import("libcpymail")


class MailAgent():
    smtp_server = {
        "name": "smtp.paulheidenreich.com",
        "port": 587,
        "login": "mail@paulheidenreich.com"
    }

    settings = {
        "from_address": None, 
        "to_addresses": None, 
        "cc_addresses": None,
        "subject": None,
        "message": None
    }

    status ={
        "success": False,
        "description": None
    } 


    def __init__(self, mail_settings = None):
        utility.load_slabstock_dotenv()
        self.settings = mail_settings
        pass

    def updateSettings(self, mail_settings):
        self.settings = mail_settings
        pass

    def send_mail(self):
        
        # mail data
        msg = MIMEMultipart()
        msg['From'] = self.settings["from_address"]
        msg['To'] = self.settings["to_addresses"]
        msg['Subject'] = self.settings["subject"]
        msg.attach(MIMEText(str(self.settings["message"]), 'plain'))

        pw = os.getenv('SMTP_KEY')
        
        try:
            # Set up the SMTP server and login if required
            server = smtplib.SMTP(self.smtp_server["name"], self.smtp_server["port"])

            # Upgrade the connection to a secure encrypted SSL/TLS connection
            server.starttls()  
            
            # Log in to the server if necessary
            if self.smtp_server["login"] and pw:
                server.login(self.smtp_server["login"], pw)
            
            # Send the email
            server.send_message(msg)
            self.status["success"] = True
            self.status["description"] = "Email sent successfully"
            print(self.status)
            
        except Exception as e:
            self.status["success"] = False
            self.status["description"] = f"Failed to send email: {e}"
            print(self.status)
        
        finally:
            server.quit()

        return self.status





