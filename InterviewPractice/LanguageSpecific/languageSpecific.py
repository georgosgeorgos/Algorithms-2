#----------------------------------------------------------------------------------------------------------------------------------
# Installation
#-------------------------
# Installing pip
sudo apt-get update
sudo apt-get install pip
# Installing any library
sudo pip install tensorflow
sudo pip install anyPythonLibraryName
# Installing from a requirements.txt
sudo pip install -r requirements.txt
# Installing from setup.py
sudo pip install .

#----------------------------------------------------------------------------------------------------------------------------------
# Working with new libraries
#-------------------------
import libraryName
help(libraryName)
print dir(libraryName) # List all methods for the library
help(libraryName.methodName)
#----------------------------------------------------------------------------------------------------------------------------------
# Headers and Libraries
#-------------------------
# Built-in
import random
# Testing
import unittest
import mock
# Others
import numpy as np # Working with matrices, numerical python
import tensorflow as tf # Working with Machine Learning
import pickle # Serialization and De-serialization (python's version of json)
import cPickle # Reading files
import gzip # Opening .gz files
# Databases
import sqlalchemy # For working with sql
# Compilation to other languages
import Cython # Convert python to C++ 
import Jython # Convert python to Java
import IronPython # Convert python to C#
# Web Framework
import django # Web Framework
import scrapy # Web scraper
import mechanize # For automating client browser interaction
# Plotting
import matplotlib # For plotting
import panda # For plotting
#----------------------------------------------------------------------------------------------------------------------------------
# Exceptions
#-------------------------
raise NotImplementedError

#----------------------------------------------------------------------------------------------------------------------------------
# Classes
#-------------------------
# Object is a special variable in python that must be inherited by all base classes in python
class NameOfClass(object):

  # Private member variables must be preceded with "__"
  __firstPrivateVariable = 0

  # Protected member variable
  firstProtectedVariable = 0

  # The constructor is called init
  def __init__(self, firstVariable, secondVariable):
    # self is a pointer to the current instance, similar to 'this' in C++
    self.firstMemberVariable = firstVariable
    self.secondMemberVariable = secondVariable
    # A static variable that counts the number of instances created for this class
    NameOfClass.counter += 1

  def getFirstVariable(self):
    return self.firstMemberVariable

  def getSecondVariable(self):
    return self.secondMemberVariable

  # Similar to toString() in Java
  def __str__(self):
    return "%s , %s" % (self.firstMemberVariable, self.secondMemberVariable)

  # Returns next iterator
  def __next__(self):
      raise NotImplementedError

# Defining a child class
class ChildClass(NameOfClass):
  def __init__(self, firstVariable, secondVariable, childVariable):
    NameOfClass.__init__(self, firstVariable, secondVariable)
    self.thirdVariable = childVariable
    self.firstProtectedVariable = 1000
  def getThirdVariable(self):
    return self.thirdVariable
#---------------------------------------------------------------------------------------------------
# Performance
#-------------------------
# Matrix Operations > Vectors > For Loops
#    For loops in python is slow
#    Vector operations using numpy is fast as it is implemented in C and uses parallel programming.
#    Matrix operation is faster than looping through vectors to perform operation

# Broadcasting => Uses C for loops instead of python for loops
# Works when:
    # one of them is a scalar
    [4,3,2] & [1] => [4, 3, 2]
    # Either one of the dimension is 1
    [4, 3] & [4, 1] => [4, 3]
    [4, 1] & [1,3] => [4, 3]
    # Both dimensions are equal
    [4, 3] & [4, 3] => [4, 3]
    # Combining them 
    [4, 3] & [1, 3] => [4, 3]
#---------------------------------------------------------------------------------------------------
