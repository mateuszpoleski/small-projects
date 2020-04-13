#finding hamiltons path in graph to solve discrete mathematic problem
def make_edges(n):
    A = [[] for _ in range(n*n)]
    for i in range(n*n):
        for j in range(n*n):
            A[i].append(0)
    for i in range(n*n):
        B = get_edges(i,n)
        for j in B:
            A[i][j] = 1

    return A


def get_edges(v1, n):
    arr = []
    if v1//n - 2 >= 0:
        if v1%n - 1 >= 0:
            arr.append(v1 - (2 * n) - 1)
        if v1%n + 1 < n:
            arr.append(v1 - (2 * n) + 1)
    if v1//n + 2 < n:
        if v1%n - 1 >= 0:
            arr.append(v1 + (2 * n) - 1)
        if v1%n + 1 < n:
            arr.append(v1 + (2 * n) + 1)
    if v1//n + 1 < n:
        if v1%n - 2 >= 0:
            arr.append(v1 + n - 2)
        if v1%n + 2 < n:
            arr.append(v1 + n + 2)
    if v1//n - 1 >= 0:
        if v1%n - 2 >= 0:
            arr.append(v1 - n - 2)
        if v1%n + 2 < n:
            arr.append(v1 - n + 2)
    return arr


def vizualize(X,n):
    A = [[] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            A[i].append(0)
    for i in range(n*n):
        w = X[i] // n
        k = X[i] % n
        A[w][k] = i
    for i in reversed(range(n)):
        for j in range(n):
            if A[i][j] // 10 == 0:
                print(A[i][j], " ", end='')
            else:
                print(A[i][j],"", end='')
        print()


def hamilton_in_place(k, n, X, DOP):
    global found
    if found:
        return
    edges = get_edges(X[k-1], n)
    for edge in edges:
        if k == n*n and edge == 0:
            found = True
            vizualize(X, n)
        else:
            if DOP[edge]:
                X[k] = edge
                DOP[edge] = False
                hamilton_in_place(k+1,n,X,DOP)
                DOP[edge] = True


def hamilton(k, n, X, DOP,A):
    global found
    if found:
        return
    for u in range(n*n):
        if A[X[k-1]][u] == 1:
            if k == n*n and u == 0:
                found = True
                vizualize(X,n)
            else:
                if DOP[u]:
                    X[k] = u
                    DOP[u] = False
                    hamilton(k+1,n,X,DOP,A)
                    DOP[u] = True


def homework():
    # a - Problem ten możemy opisać jako znalezienie cyklu Hamiltona w grafie którego wierzchołkami są pola na szachownicy,
    #     a krawędź między polami u v istnieje gdy skoczek mógłby wykonać ruch z u do v.
    # b - Jak na pythona chyba działa całkiem szybko,
    #     zrobiłem także wersje która nie potrzebuje przechowywać informacji o krawędziach (zajmuje znacznie mniej pamięci), jednak działa nieco wolniej.
    # c - Łatwo zauważyć, że skoczek wykonuje ruchy jedynie z białych pól na czarne, i z czarncyh na białe. W takim razie nasz graf zawsze jest dwudzielny. Jeśli graf dwudzielny ma mieć
    #     szansę na posiadanie cyklu Hamiltona, to ilość wierzchołków w G1 i G2 musi być taka sama (pokazaliśmy na ćwiczeniach), czyli liczba białych i czarnych pól musi być taka sama.
    #     taka sytuacja występuje gdy n jest parzyste.
    global found
    n = int(input("Podaj n: "))
    if n%2 == 1:
        print("Odpowiednia droga nie może istnieć")
        return
    else:
        X = [0] * n * n
        DOP = [True] * n * n
        DOP[0] = False
        A = make_edges(n)
        found = False
        print("Znaleziona Droga: ")
        hamilton(1, n, X, DOP,A)
        #hamilton_in_place(1, n, X, DOP)


homework()

