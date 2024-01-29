global_funcs = {}


def decorator(key):
    def dec(func):
        global_funcs[key] = func
        return func
    return dec


@decorator('a')
def funca():
    print('funca')

@decorator('b')
def funcb():
    print('funcb')

@decorator('c')
def funcc():
    print('funcc')


for k, v in global_funcs.items():
    print(k)
    v()
