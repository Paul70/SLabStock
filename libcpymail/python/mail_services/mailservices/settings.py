class MailSettings():
    address_from = None
    address_to = None
    subject = None
    message = None

    def __init__(self, mail_address_from = None, mail_address_to = None, mail_subject = None, mail_message = None):
        self.address_from = mail_address_from
        self.address_to = mail_address_to
        self.subject = mail_subject
        self.message = mail_message
        pass

    def setFrom(self, address):
        self.address_from = address
        pass

    def setTo(self, address):
        self.address_to = address
        pass

    def setSubject(self, subject):
        self.subject = subject
        pass

    def setMessage(self, message):
        self.subject = message
        pass

    def getFrom(self):
        return self.address_from

    def getTo(self):
        return self.address_to

    def getSubject(self):
        return self.subject

    def getMessage(self):
        return self.subject
    