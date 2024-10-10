# 17875 - легкий
# from functools import *


# def move(h):
#     a=[]
#     if h-2>=0:
#         a.append(h-2)
#     if h-5>=0:
#         a.append(h-5)
#     if (h//3)>=0:
#         a.append(h//3)
#     return a


# @lru_cache(None)
# def games(s):
#     if s<=19:
#         return "W"
#     if any(games(x)=="W" for x in move(s)):
#         return "P1"
#     if all(games(x)=="P1" for x in move(s)):
#         return "B1"
#     if any(games(x)=="B1" for x in move(s)):
#         return "P2"
#     if all(games(x)=="P1" or games(x)=="P2" for x in move(s)):
#         return "B2"

# for i in range(20,200):
#     if games(i)=='B2':
#         print(i)


# 471 - средний

# from functools import *


# def move(h):
#     return h+2,h*3


# @lru_cache(None)
# def games(s,f):
#     if s>=f:
#         return "W"
#     if any(games(x,f)=="W" for x in move(s)):
#         return "P1"
#     if all(games(x,f)=="P1" for x in move(s)):
#         return "B1"
#     if any(games(x,f)=="B1" for x in move(s)):
#         return "P2"
#     if all(games(x,f)=="P1" or games(x,f)=="P2" for x in move(s)):
#         return "B2"

# for i in range(1,200):
#     if games(5,i)=='B2':
#         print(i,games(5,i))


# 5441 - сложный - аналитикой легче


# from functools import *


# def move(h):
#     return h+10,h*2

# @lru_cache(None)
# def games(s):
#     if s>=82:
#         return "W"
#     if all(games(x)=="W" for x in move(s)): #петя сделал первый ход
#         return "P1->B0"
#     if any(games(x)=="P1->B0" or games(x)=="W" for x in move(s)): #ваня сделал первый ход
#         return "B1->P1"
#     if all(games(x)=="B1->P1"  or games(x)=="W" for x in move(s)): #петя сделал второй ход
#         return "P2->B1"

# for i in range(1,82):
#     if games(i)=='B1->P1':
#         print(i,games(i))



# @lru_cache(None)
# def games(s):
#     if s>=82:
#         return "W"
#     if all(games(x)=="W" for x in move(s)): #петя сделал первый ход
#         return "P1->B0"
#     if any(games(x)=="P1->B0" for x in move(s)): #ваня сделал первый ход
#         return "B1->P1"
#     if all(games(x)=="B1->P1"  or games(x)=="W" for x in move(s)): #петя сделал второй ход
#         return "P2->B1"

# for i in range(1,82):
#     if  games(i)=='P2->B1':
#         print(i,games(i))


# @lru_cache(None)
# def games(s):
#     if s>=82:
#         return "W"
#     if all(games(x)=="W" for x in move(s)): #петя сделал первый ход
#         return "P1->B0"
#     if any(games(x)=="P1->B0" for x in move(s)): #ваня сделал первый ход
#         return "B1->P1"
#     if all(games(x)=="B1->P1"  or games(x)=="W" for x in move(s)): #петя сделал второй ход
#         return "P2->B1"
#     if any(games(x)=="P2->B1" for x in move(s)): #петя сделал второй ход
#         return "B2->P2"

# for i in range(1,82):
#     if  games(i)=='B2->P2':
#         print(i,games(i))




# 1374 - гроб

# from functools import *


# def move(g):
#     kuch_1,kuch_2=g
#     return (kuch_1+10,kuch_2),(kuch_1*2,kuch_2),(kuch_1,kuch_2+10),(kuch_1,kuch_2*2)

# @lru_cache(None)
# def games(g):
#     kuch_1,kuch_2=g
#     s=kuch_1+kuch_2
#     if s>=107 and s<=170:
#         return "W"
#     if s>170:
#         return "F"
#     if any(games(x)=="W" for x in move(g)): #петя сделал первый ход
#         return "P1"
#     if any(games(x)=="P1" for x in move(g)): #ваня сделал первый ход
#         return "B1"

# for i in range(1,101):
#     g=5,i
#     if games(g)=="B1":
#         print(i,games(g))   19 номер
#         break

# @lru_cache(None)  20 +аналитика, проверить 42,43,44,45
# def games(g):
#     kuch_1,kuch_2=g
#     s=kuch_1+kuch_2
#     if s>=107 and s<=170:
#         return "W"
#     if s>170:
#         return "F"
#     if any(games(x)=="F" for x in move(g)) and not(any(games(x)=="W" for x in move(g))): #петя сделал первый ход
#         return "P1"
#     if any(games(x)=="P1" for x in move(g)) and not(any(games(x)=="W" for x in move(g))): #ваня сделал первый ход
#         return "B1"
# for i in range(1,101):
#     g=5,i
#     if games(g)=="B1":
#         print(i,games(g))



# @lru_cache(None)  
# def games(g):
#     kuch_1,kuch_2=g
#     s=kuch_1+kuch_2 #пункт 21
#     if s>=107 and s<=170:
#         return "W"
#     if s>170:
#         return "F"
#     if any(games(x)=="W" for x in move(g)): 
#         return "P1"
#     if all(games(x)=="P1" for x in move(g)): 
#         return "B1"
#     if any(games(x)=="B1" for x in move(g)):
#         return "P2"
#     if all(games(x)=="P1" or games(x)=="P2" for x in move(g)): 
#         return "B2"
# for i in range(1,101):
#     g=5,i
#     if games(g)=="B2":
#         print(i,games(g))
