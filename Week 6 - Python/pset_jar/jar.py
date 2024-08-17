class Jar:

    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError()

        self._capacity = capacity
        self._size = 0

    def __str__(self):
        cookie = '🍪'
        return self._size * cookie

    def deposit(self, n):
        if n < 0 or self._size + n > self._capacity:
            raise ValueError(
                "Cannot deposit more cookies than the jar's capacity")
        self._size += n

    def withdraw(self, n):
        if n < 0 or n > self._size:
            raise ValueError(
                "Cannot withdraw more cookies than available in the jar")
        self._size -= n

        @property
        def capacity(self):
            return self._capacity

        @property
        def size(self):
            print('size')
            return self._size


jar = Jar(12)
jar.deposit(2)
jar.withdraw(1)

print(str(jar))
print(jar._size)

jar.withdraw(100)
