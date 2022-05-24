#!/usr/bin/python
import sys
import time
import re
import socket
print "####################################################\n"
###########################################################
print "My name is %s and weight is %d kg!" % ('Zara', 21)
print "####################################################\n"
###########################################################
i=1
if False:
	print "True"
elif i is not 0:
	print "i is not 0"
else:
	print "Answer"
	print "False"
print "####################################################\n"
###########################################################
file_name = "output.txt"
file_finish = "output.txt"
try:
  # open file stream
  file = open(file_name, "w")
except IOError:
  print "There was an error writing to", file_name
  sys.exit()
print "Enter '", file_finish,
print "' When finished"
file.close()
print "####################################################\n"
###########################################################
word = 'word\n'
sentence = "This is a sentence.\n"
paragraph = """This is a paragraph. It is
made up of multiple lines and sentences.\n"""
print word + sentence + paragraph
print "####################################################\n"
###########################################################
x='foo'
sys.stdout.write(x + '\n')
print "####################################################\n"
###########################################################
a = b = c = 1
print "a=%d b=%d c=%d" %(a , b , c)
a, b, c = "bear ", "bill ", "john \n"
print a + b + c

print "####################################################\n"
###########################################################

str = 'Hello World!'

print str          # Prints complete string
print str[0]       # Prints first character of the string
print str[2:5]     # Prints characters starting from 3rd to 5th
print str[2:]      # Prints string starting from 3rd character
print str * 2      # Prints string two times
print str + "TEST" # Prints concatenated string

print "####################################################\n"
###########################################################

templist = [ 'abcd', 786 , 2.23, 'john', 70.2 ]
tinylist = [123, 'john']

print templist          # Prints complete list
print templist[0]       # Prints first element of the list
print templist[1:3]     # Prints elements starting from 2nd till 3rd 
print templist[2:]      # Prints elements starting from 3rd element
print tinylist * 2  # Prints list two times
print templist + tinylist # Prints concatenated lists


print "####################################################\n"                                                                                                                                                                            
###########################################################
tuple = ( 'abcd', 786 , 2.23, 'john', 70.2  )
tinytuple = (123, 'john')

print tuple           # Prints complete list
print tuple[0]        # Prints first element of the list
print tuple[1:3]      # Prints elements starting from 2nd till 3rd 
print tuple[2:]       # Prints elements starting from 3rd element
print tinytuple * 2   # Prints list two times
print tuple + tinytuple # Prints concatenated lists

print "####################################################\n"                                                                                                                                                                            
###########################################################


tuple = ( 'abcd', 786 , 2.23, 'john', 70.2  ) # can not modified
list = [ 'abcd', 786 , 2.23, 'john', 70.2  ] # can modified
#tuple[2] = 1000    # Invalid syntax with tuple
print "old value=%f" %(list[2])
list[2] = 1000     # Valid syntax with list
print "new value=%d" %(list[2])
print "####################################################\n"                                                                                                                                                                            
###########################################################

dict = {}
dict['one'] = "This is one"
dict[2]     = "This is two"

tinydict = {'name': 'john','code':6734, 'dept': 'sales'}


print dict['one']       # Prints value for 'one' key
print dict[2]           # Prints value for 2 key
print tinydict          # Prints complete dictionary
print tinydict.keys()   # Prints all the keys
print tinydict.values() # Prints all the values

print "####################################################\n"                                                                                                                                                                            
###########################################################
var = 100

if ( var  == 100 ) : 
	print "Value of expression is 100"
print "Good bye!"
print "####################################################\n"                                                                                                                                                                            
###########################################################
list1 = ['physics', 'chemistry', 1997, 2000];

print list1
del list1[2];
print "After deleting value at index 2 : "
print list1
print "####################################################\n"                                                                                                                                                                            
###########################################################
list = [1,'john',2,3,'bill']
for x in list:
	print x

if 'bear' in list:
	print "john is in list"
else:
	print "john is not in list"

print len(list)
print "####################################################\n"                                                                                                                                                                            
###########################################################
dict = {'Name': 'Zara', 'Age': 7, 'Class': 'First'}

dict['Age'] = 8; # update existing entry
dict['School'] = "DPS School"; # Add new entry


print "dict['Age']: ", dict['Age']
print "dict['School']: ", dict['School']
print "####################################################\n"                                                                                                                                                                            
###########################################################
dict = {'Name': 'Zara', 'Age': 7, 'Name': 'Manni'}
for x in dict:
	print len(dict)
	print "dict['Name']: ", dict['Name']

print "####################################################\n"                                                                                                                                                                            
###########################################################
localtime = time.asctime( time.localtime(time.time()) )
print "Local current time :", localtime

print "####################################################\n"                                                                                                                                                                            
###########################################################
def changeme( mylist ):
	"This changes a passed list into this function"
	mylist = [1,2,3,4]; # This would assig new reference in mylist
	print "Values inside the function: ", mylist
	return

# Now you can call changeme function
mylist = [10,20,30]
changeme( mylist )
print "Values outside the function: ", mylist

print "####################################################\n"                                                                                                                                                                            
###########################################################
def printinfo( name, age = 35 ):
	"This prints a passed info into this function"
	print "Name: ", name
	print "Age ", age
	return;

# Now you can call printinfo function
printinfo( age=50, name="miki" )
printinfo( name="miki" )
print "####################################################\n"                                                                                                                                                                            
###########################################################
def printinfo( arg1, *vartuple ):
	"This prints a variable passed arguments"
	print "Output is: "
	print arg1
	for var in vartuple:
		print var
	return;

list = [0x11, 0x22, 0x33, 0x44]
# Now you can call printinfo function
printinfo( 10 )
printinfo( 70, 60, 50, list, "hi bear" )
print "####################################################\n"                                                                                                                                                                            
###########################################################
total = 0; # This is global variable.
# Function definition is here
def sum( arg1, arg2 ):
	# Add both the parameters and return them."
	total = arg1 + arg2; # Here total is local variable.
	print "Inside the function local total : ", total
	return total;

# Now you can call sum function
#total = sum( 10, 20 );
sum(10,20)
print "Outside the function global total : ", total 
print "####################################################\n"                                                                                                                                                                            
###########################################################
# Open a file
fo = open("foo.txt", "wb")
fo.write( "Python is a great language.\nYeah its great!!\n");
# Close opend file
fo.close()

fo = open("foo.txt", "r+")
str = fo.read(5); #read file 0~5 offset
print "Read String is : ", str
position = fo.tell();
print "Current file position : ", position

str = fo.read(10); # read 6~10
print "Read String is : ", str

position = fo.seek(0, 0);
str = fo.read(15);
print "Again read String is : ", str

# Close opend file
fo.close()
print "####################################################\n"                                                                                                                                                                            
###########################################################
try:
	fh = open("foo1.txt", "w")
	try:
		fh.write("This is my test file for exception handling!!")
	finally:
		print "Going to close the file"
		fh.close()
except IOError:
	print "Error: can\'t find file or read data"
print "####################################################\n"                                                                                                                                                                            
###########################################################
class Employee:
	'Common base class for all employees'
	empCount = 0

	def __init__(self, name, salary):
		self.name = name
		self.salary = salary
		Employee.empCount += 1
   
	def displayCount(self):
		print "Total Employee %d" % Employee.empCount

	def displayEmployee(self):
		print "Name : ", self.name,  ", Salary: ", self.salary

"This would create first object of Employee class"
emp1 = Employee("Zara", 2000)
"This would create second object of Employee class"
emp2 = Employee("Manni", 5000)

emp1.displayEmployee()
emp2.displayEmployee()
print "Total Employee %d" % Employee.empCount
print "####################################################\n"                                                                                                                                                                            
###########################################################

class Parent:        # define parent class
	parentAttr = 100
	def __init__(self):
		print "Calling parent constructor"

	def parentMethod(self):
		print 'Calling parent method'

	def setAttr(self, attr):
		Parent.parentAttr = attr

	def getAttr(self):
		print "Parent attribute :", Parent.parentAttr

class Sub_Parent:
	sub_parentAttr = 200
	def __init__(self):
		print "Calling sub_parent constructor"

	def sub_parentMethod(self):
		print "Calling sub_parent method"

	def set_sub_Attr(self, attr):
		Sub_Parent.sub_parentAttr = attr

	def get_sub_Attr(self):
		print "Sub Parent attribut :", Sub_Parent.sub_parentAttr

class Child(Parent,Sub_Parent): # define child class
   def __init__(self):
      print "Calling child constructor"

   def childMethod(self):
      print 'Calling child method'

c = Child()          # instance of child
c.childMethod()      # child calls its method
c.parentMethod()     # calls parent's method
c.setAttr(200)       # again call parent's method
c.getAttr()          # again call parent's method
c.sub_parentMethod()
c.set_sub_Attr(300)
c.get_sub_Attr()
print "####################################################\n"                                                                                                                                                                            
###########################################################
class Vector:
	def __init__(self, a, b):
		self.a = a
		self.b = b

	def __str__(self):
		return "=> %d %d" % (self.a, self.b)
   
	def __add__(self,other):
		return Vector(self.a + other.a, self.b + other.b)

v1 = Vector(2,10)
v2 = Vector(5,-3)
print v1 + v2
print "####################################################\n"                                                                                                                                                                            
###########################################################
class JustCounter:
	__secretCount = 0
  
	def count(self):
		self.__secretCount += 1
		print self.__secretCount

counter = JustCounter()
counter.count()
counter.count()
print counter._JustCounter__secretCount
print "####################################################\n"                                                                                                                                                                            
###########################################################
line = "Cats are smarter than dogs"

matchObj = re.match( r'(.*) are (.*?) .*', line)

if matchObj:
	print "matchObj.group() : ", matchObj.group()
	print "matchObj.group(1) : ", matchObj.group(1)
	print "matchObj.group(2) : ", matchObj.group(2)
else:
	print "No match!!"

searchObj = re.search( r'(.*) are (.*?) .*', line, re.M|re.I) #re.I =>low case high case

if searchObj:
	print "searchObj.group() : ", searchObj.group()
	print "searchObj.group(1) : ", searchObj.group(1)
	print "searchObj.group(2) : ", searchObj.group(2)
else:
	print "Nothing found!!"

matchObj = re.match( r'dogs', line, re.M|re.I)
if matchObj:
	print "match --> matchObj.group() : ", matchObj.group()
else:
	print "No match!!"

searchObj = re.search( r'dogs', line, re.M|re.I)
if searchObj:
	print "search --> searchObj.group() : ", searchObj.group()
else:
	print "Nothing found!!"

phone = "2004-959-559 # This is Phone Number"

# Delete Python-style comments
num = re.sub(r'#.*$', "", phone)
print "Phone Num : ", num

# Remove anything other than digits
num = re.sub(r'\D', "", phone)    
print "Phone Num : ", num

# Find string count
num = line.count("ar")
print "string count ",num
print "####################################################\n"                                                                                                                                                                            
###########################################################


print "####################################################\n"                                                                                                                                                                            
###########################################################
print "####################################################\n"                                                                                                                                                                            
###########################################################
print "####################################################\n"                                                                                                                                                                            



#str = raw_input("\nPress the enter : ")
#print "Receive input is : ", str
###########################################################
###########################################################
###########################################################
