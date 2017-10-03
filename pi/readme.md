# Pi Master
The master is meant to translate user input for the ardiuno controller to
consume.

## Setup
Installing the python dependencies requires a few c/c++ libraries as well
as compiler utilities:
```bash
sudo apt-get update
# Install build tools
sudo apt-get install gcc build-essential -y
# Install required header files
sudo apt-get install python3-dev libbluetooth-dev -y
```

After that, you should create a virtualenv with the python dependencies:
```bash
virtualenv env
. ./env/bin/activate
pip install --editable .
```
