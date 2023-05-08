import numpy as np
# step 0:
teta = 0.2
alpha = 0.8
sample = []
target = []
weight = np.zeros((63, 7))
bias = np.zeros((7))
y = np.zeros((7))
y_in = np.zeros((7))
file = open("sample.txt", "r")
for line in file:
    row = line.split()
    for i in range(len(row)):
        row[i] = float(row[i])
    sample.append(row)
file = open("target.txt", "r")
for line in file:
    row = line.split()
    for i in range(len(row)):
        row[i] = float(row[i])
    target.append(row)
# step 1:
active = True
n = 0
while active:
    if n > 0:
        print("Repeat training\n")
    active = False
    current_number = 0
    # step 2:
    while current_number < 14:
        i = 0
        x = []
        t = []
        # step 3:
        while i < 63:
            x.append(sample[current_number][i])
            i += 1
        i = 0
        while i < 7:
            t.append(target[current_number % 7][i])
            i += 1
        j = 0
        # step 4 , 5:
        while j < 7:
            i = 0
            sum = 0
            y_in = bias + np.dot(x, weight)
            i = 0
            while i < 63:
                if y_in[j] > teta:
                    y[j] = 1
                elif y_in[j] < -teta:
                    y[j] = -1
                else:
                    y[j] = 0
                if t[j] != y[j]:
                    active = True
                    bias[j] = bias[j] + alpha*t[j]
                    weight[i][j] = weight[i][j] + alpha*t[j]*x[i]
                i += 1
            j += 1
        current_number += 1
    n += 1
# Write weight and bias in the "weight.txt" file
filename = 'weight.txt'
with open(filename, 'w') as file_object:
    file_object.write("weight: \n")
    s = str(weight)
    file_object.write(s)
    file_object.write("\n\nbias: \n")
    s = str(bias)
    file_object.write(s)
    file_object.write("\n\nNumber of trainings: ")
    s = str(n)
    file_object.write(f"{s}\n\n")
# 1-7:A-K:font1   8-14:A-K:font2    15-21:A-K:font3
pattern_number = int(input("Enter the pattern number you want: "))
pattern_number = pattern_number - 1
i = 0
x = []
z = []
sum = np.zeros((7))
while i < 63:
    x.append(sample[pattern_number][i])
    i += 1
sum = bias + np.dot(x, weight)
j = 0
while j < 7:
    if sum[j] > teta:
        z.append(1)
    elif sum[j] < -teta:
        z.append(-1)
    j += 1
current_number = 0
sw = 0
t = []
# append pattern in the "weight.txt" file
while current_number < 7:
    if z[current_number] == 1:
        sw = 1
        if current_number == 0:
            with open(filename, 'a') as file_object:
                s1 = str(z)
                s2 = str(current_number + 1)
                file_object.write(f"A: y[{s2}]= {s1}")
        elif current_number == 1:
            with open(filename, 'a') as file_object:
                s1 = str(z)
                s2 = str(current_number + 1)
                file_object.write(f"B: y[{s2}]= {s1}")
        elif current_number == 2:
            with open(filename, 'a') as file_object:
                s1 = str(z)
                s2 = str(current_number + 1)
                file_object.write(f"C: y[{s2}]= {s1}")
        elif current_number == 3:
            with open(filename, 'a') as file_object:
                s1 = str(z)
                s2 = str(current_number + 1)
                file_object.write(f"D: y[{s2}]= {s1}")
        elif current_number == 4:
            with open(filename, 'a') as file_object:
                s1 = str(z)
                s2 = str(current_number + 1)
                file_object.write(f"E: y[{s2}]= {s1}")
        elif current_number == 5:
            with open(filename, 'a') as file_object:
                s1 = str(z)
                s2 = str(current_number + 1)
                file_object.write(f"J: y[{s2}]= {s1}")
        if current_number == 6:
            with open(filename, 'a') as file_object:
                s1 = str(z)
                s2 = str(current_number + 1)
                file_object.write(f"K: [{s2}]= {s1}")
    current_number += 1
if sw == 0:
    with open(filename, 'a') as file_object:
        file_object.write(f"Error")
