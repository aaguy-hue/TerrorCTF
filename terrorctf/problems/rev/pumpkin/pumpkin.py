import base64

def unshift(target):
  for i in target:
    target = target.replace(i, str(ord(i)+1) + " ")
  target = target.split()
  for i in range(len(target)):
    target[i] = chr(int(target[i]))
  target = "".join(target)
  return target
bestcrust = "YnV0dGVyeQ=="
bestfilling = "Z29vZXk="
besttopping = "vghoodcbqd`l"
byte = base64.b64decode(bestcrust)
byte2 = base64.b64decode(bestfilling)
def bake():
  goodtoken = 0
  token = 0
  while token == 0:
    print("---Answer with adjectives---")
    crust = str(input("Best kind of crust crust? "))
    if crust == byte.decode("utf-8"):
      print("correct")
      goodtoken += 1
    elif crust != byte.decode("utf-8"):
      token += 1
    filling = str(input("Best kind of filling? "))
    if filling == byte2.decode("utf-8"):
      print("correct")
      goodtoken += 1
    elif filling != byte2.decode("utf-8"):
      token+=1
    print("---Answer with a noun---")
    topping = str(input("Best topping? "))
    if topping == unshift(besttopping):
      print("correct")
      token+=1
      goodtoken += 1
    elif topping != unshift(besttopping):
      token+=1
  if goodtoken == 3:
    f = open("pumpkinflag.txt", "r")
    b = f.read()
    print(b)
print("===========================================================")
print("""
  _____                       _    _       _____
 |  __ \                     | |  (_)     |  __ \      
 | |__) |   _ _ __ ___  _ __ | | ___ _ __ | |__) |   _ 
 |  ___/ | | | '_ ` _ \| '_ \| |/ / | '_ \|  ___/ | | |
 | |   | |_| | | | | | | |_) |   <| | | | | |   | |_| |
 |_|    \__,_|_| |_| |_| .__/|_|\_\_|_| |_|_|    \__, |
                       | |                        __/ |
                       |_|                       |___/ 
""")
print("===========================================================")
print("Do you know the ways of the Py?")
npc = """
x - Exit
y - Help
z - Bake
"""
print(npc)
while 1:
  n = input(">>> ")
  if n == "y":
    print(npc)
  elif n == "x":
    break
  elif n == "z":
    bake()
