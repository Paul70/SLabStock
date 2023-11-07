import subprocess

bashCommand = "conan install . -pr ./conanprofile"
process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
output, error = process.communicate()
