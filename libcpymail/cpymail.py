import os
import sys
sys.path.append(f"{os.getcwd()}/python/mail_services/mailservices")

import python.mail_services.mailservices.mailagent as mailagent
import protobuf.mailsettings_pb2

def cpy_send_mail(protobuf_serialized_string):
    # desrialize input string and create protobuf dictionary object
    protobuf_serialized_string = protobuf_serialized_string.encode('utf-8')
    protobuf_mail_settings = protobuf.mailsettings_pb2.MailSettings()
    protobuf_mail_settings.ParseFromString(bytes(protobuf_serialized_string))

    mail_settings = {
        "from_address": "mail@paulheidenreich.com", 
        "to_addresses": protobuf_mail_settings.to_addresses[0], 
        "cc_addresses": None,
        "subject": protobuf_mail_settings.subject,
        "message": protobuf_mail_settings.message
    }

    agent = mailagent.MailAgent(mail_settings)
    mail_status = agent.send_mail()

    protobuf_request_result = protobuf.mailsettings_pb2.RequestResult()
    if mail_status["success"]:    
        protobuf_request_result.status_code = 200
    else:
        protobuf_request_result.status_msg = 400
    protobuf_request_result.status_msg = mail_status["description"]
    print(protobuf_request_result)

    serialized_reply = protobuf_request_result.SerializeToString()
    return serialized_reply


if __name__ == "__main__":
    dto = '\n\030mail@paulheidenreich.com"\tStar Wars*\025Obi Wan: Hello there!'
    result = cpy_send_mail(dto)
    print(result)

