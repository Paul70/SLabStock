import os
import shutil
import subprocess

def create_runtime_venv():
    print(os.getcwd())

    runtime_bin = "./build/Debug/bin" # ist eig conan build_folder
    venv_path = os.path.join(runtime_bin, '.venv')
    assert os.path.isdir(runtime_bin)

    if not os.path.isdir(venv_path):
        subprocess.run(['python3', '-m', 'venv', '.venv'], cwd=runtime_bin, capture_output=False)
    
    try:
        shutil.copy("./requirements.txt", venv_path)
    except Exception as e:
        print(f"Error copying file: {e}")

    pip_path = os.path.join(venv_path, 'bin', 'pip')
    subprocess.run([pip_path, "install", "-r", "requirements.txt"], capture_output=False)


    #subprocess.run(command, cwd=runtime_bin, capture_output=False)
    #subprocess.call(f"{activate_script} && pip install requests", shell=False)
    #subprocess.run(["deactivate"], cwd=runtime_bin, capture_output=False)
    #req = "pip install -r" + os.getcwd() + "/requirements.txt"
    #subprocess.run(req, cwd=runtime_bin, capture_output=False)
    #subprocess.run("deactivate", cwd=runtime_bin, capture_output=False)


    # Run the command in a specific directory
    #result = subprocess.run(command, cwd=runtime_bin, capture_output=False)
    pass

if __name__ == "__main__":
    create_runtime_venv()