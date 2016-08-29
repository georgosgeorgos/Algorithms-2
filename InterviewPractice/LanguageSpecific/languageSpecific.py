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

# Defining a child class
class ChildClass(NameOfClass):
  def __init__(self, firstVariable, secondVariable, childVariable):
    NameOfClass.__init__(self, firstVariable, secondVariable)
    self.thirdVariable = childVariable
    self.firstProtectedVariable = 1000
  def getThirdVariable(self):
    return self.thirdVariable
