import sys

def factor(num, primes):
    for prime in primes:
        if num % prime == 0:
            return prime
    return None

def get_biggest_prime_less_than_x(x):
    primes = []
    for i in range(2, x):
        for prime in primes:
            if i % prime == 0:
                break
        else:
            primes.insert(0, i)

    if primes:
        return primes[0], factor(primes[0] + 1, primes)
    else:
        return None, None


if __name__ == '__main__':
    if len(sys.argv) < 1:
        print('No upper bound is given!')
    else:
        print(get_biggest_prime_less_than_x(int(sys.argv[1])))

