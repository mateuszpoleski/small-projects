#coloring graph to solve discrete mathematics problem
def make_adj_matrx(n):
    A = [[] for _ in range(n + 1)]
    for i in range(n + 1):
        for j in range(n + 1):
            A[i].append(1)
    for i in range(n + 1):
        A[i][i] = 0
        A[i][0] = 0
        A[0][i] = 0
    return A


def make_edges(file):
    while True:
        line = file.readline()
        if line:
            l = line.split()
            v = int(l[0])
            u = int(l[1])
            A[u][v] = 0
            A[v][u] = 0
        else:
            break


def vizualize(val,colors,alg):
    print()
    print("Rozwiązanie z wykorzystaniem",alg)
    print("Odpowiedzią jest", val, ", przykładowe egzaminy")
    print()
    for j in range(1, val + 1):
        print("Dzień", j, ": ", end="")
        for k, c in enumerate(colors):
            if c == j:
                print(k, end=" ")
        print()


def is_color_valid(n, v, color, colors):
    for i in range(n+1):
        if A[v][i] == 1 and colors[i] == color:
            return False
    return True


def color_graph(n, v, k, colors):
    if v == n+1:
        return True
    for c in range(1,k+1):
        if is_color_valid(n,v,c,colors):
            colors[v] = c
            if color_graph(n,v+1,k,colors):
                return True
            colors[v] = 0
    return False


def backtracking_coloring(n):
    for i in range(n + 1):
        colors = [0] * (n + 1)
        if color_graph(n, 1, i, colors):
            vizualize(i, colors, "backtrackingu.")
            #print(is_coloring_correct(n, colors))
            break


def get_smallest_color(n,u,colors):
    avl_colors = [*range(1,n+1)]
    for v in range(n+1):
        if A[u][v] == 1 and colors[v] in avl_colors:
            avl_colors.remove(colors[v])
    return min(avl_colors)


def greedy_coloring(n):
    colors = [0] * (n + 1)
    for u in range(1,n+1):
        colors[u] = get_smallest_color(n,u,colors)
    val = max(colors)
    vizualize(val, colors, "algorytmu zachłannego.")
    #print(is_coloring_correct(n,colors))


def is_coloring_correct(n,colors):
    for v in range(1,n+1):
        c = colors[v]
        for u in range(1,n+1):
            if A[v][u] == 1 and c == colors[u]:
                return False
    return True


file_name = input("Podaj nazwę pliku") 
file = open(file_name, "r")

n = int(file.readline())
A = make_adj_matrx(n)
make_edges(file)

file.close()

greedy_coloring(n)
backtracking_coloring(n)



# a - Problem ten możemy przedstawić jako znalezienie najmniejszego kolorowania grafu, w którym wierzchołkami są egzaminy,
#     a krawędziami kolizje między nimi, tzn. że conajmniej jeden student uczestniczy w obu egzaminach u v. Ponieważ w pliku
#     otrzymujemy pary bez kolizji, to krawędziami naszego grafu będzie graf pełny z wyłączeniem krawędzi z pliku (oraz krawędzi
#     z v do v). W otrzymanym kolorowaniu, wszystkie wierzchołki(egzaminy) o tym samym kolorze mogą odbyć się tego samego dnia.
# b - W takim przypadku powinniśmy skorzystać z algorytmu zachłannego, którego złożoność jest liniowa. Jeśli zależy nam na znalezieniu
#     jak najbardziej precyzyjnej odpowiedzi możemy algorytm ten zrandomizować i wywołać wielokrotnie (dzięki liniowej złożoności nie
#     będzie to stnowiło problemu).
# c - ()


