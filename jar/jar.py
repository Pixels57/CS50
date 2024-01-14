class Jar:
    count = 0
    theme ="🍪'
    def __init__(self, capacity):
        if capacity > 0:
            self._capacity = capacity
        else:
             raise ValueError('Capacity cannot be zero or a negative number.')
             #raise ValueError



    def __str__(self):
        return str(Jar.theme * Jar.count)


    def deposit(self, n):
        c = Jar.count + n
        if c > self.capacity:
            raise ValueError("Can't deposit such cookies it will exceed jar :'(")
        else:
            count = c

    def withdraw(self, n):
        c = count - n
        if count < 0:
            raise ValueError("Not that much of cookies")
        else:
            count = c

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return count


def main():
    jar =Jar(4)
    print(str(jar.capacity))
    jar.deposit(2)
    print(str(jar))

main()