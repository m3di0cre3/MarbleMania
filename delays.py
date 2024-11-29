file = open(r"C:\Users\anand\OneDrive\Documents\peroxidetimes.txt", "r")
prev = int(float(file.readline())*1000)
while True:
    curr = int(float(file.readline())*1000)
    print(curr-prev)
    prev = curr