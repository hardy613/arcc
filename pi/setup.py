from setuptools import setup, find_packages

setup(
    name = 'pi_master',
    version = '0.0.0',
    packages=find_packages(),
    scripts=[
        'bin/keyboard_connect'
    ],
    install_requires=[
        'pybluez==0.22'
    ]
)
