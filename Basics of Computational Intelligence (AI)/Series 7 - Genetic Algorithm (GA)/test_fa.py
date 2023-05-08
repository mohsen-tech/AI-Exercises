import numpy as np
from numpy import random as rn
n = 70


def initial_population_8queen(n):
    list1 = [0, 1, 2, 3, 4, 5, 6, 7]
    return(rn.choice(list1, size=(n, 8)))


population = initial_population_8queen(n)
# print(population)


def fitness(population):
    fit = []
    for i in range(len(population)):
        colide = 0
        for j in range(len(population[i])):
            k = j+1
            while k < len(population[i]):
                if population[i][j] == population[i][k] or abs(population[i][j] - population[i][k]) == abs(j - k):
                    colide += 1
                k += 1
        fit.append(28 - colide)
    return(fit)


fit = fitness(population)
# print(fitness)


def random_selection(population):
    rn.shuffle(population)
    return(population)


def relative_selection(fitness, population):
    population_2 = []
    for i in range(len(population)):
        for j in range(fitness[i]):
            population_2.append(population[i])
    population_2 = np.array(population_2, int)
    rn.shuffle(population_2)
    return(population_2[0:len(population)])


def one_point_crossover(p):
    ch = p.copy()
    for i in range(len(ch)):
        if i % 2 == 0:
            x = rn.randint(8)
            x += 1
            s = list(ch[i][0:x])
            ch[i][0:x] = ch[i+1][0:x]
            ch[i+1][0:x] = s
    return(ch)


def mutation(ch):
    s = 4/100
    n = int(s * len(ch))
    for i in range(n):
        x = rn.randint(len(ch))
        list1 = [0, 1, 2, 3, 4, 5, 6, 7]
        y = rn.choice(list1)
        z = rn.choice(list1)
        ch[x][y] = z
    return(ch)


def SteadyStateReplacement(pop, ch, fit):
    s = 4/100
    x = int(s * len(pop))
    y = len(pop) - x
    rn.shuffle(pop)

    population = []
    for i in range(y):
        population.append(pop[i])

    for i in range(x):
        j = fit.index(max(fit))
        population.append(ch[j])
        fit[j] = 0

    population = np.array(population, int)
    return(population)


#population = random_selection(population)
active = True
d = 0
while active:
    pool = relative_selection(fit, population)
    children = one_point_crossover(pool)
    children = mutation(children)
    fit_ch = fitness(children)
    population = SteadyStateReplacement(
        population, children, fit_ch)
    fit = fitness(population)
    if max(fit) == 28:
        s = fit.index(max(fit))
        print(population[s])
        print(d)
        active = False
    d += 1
    if d % 1000 == 0:
        print(max(fit))
        print(d)
