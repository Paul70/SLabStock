from setuptools import setup

setup (
    name='ypyTA',
    version='0.1.0',
    description='A python module for technical analysis of stocks based on yfinance',
    author='Paul Heidenreich',
    author_email='mail@paulheidenreich.com',
    license='BSD 2-clause',
    packages=['ypyTA'],
    install_requires=['yfinance>=0.2.41'],

    classifiers=[
        'Development Status :: 1 - Planning',
        'Intended Audience :: Science/Research',
        'License :: OSI Approved :: BSD License',  
        'Operating System :: POSIX :: Linux',        
        'Programming Language :: Python :: 3.10'
        ]
)