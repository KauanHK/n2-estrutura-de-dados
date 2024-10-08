import matplotlib.pyplot as plt


x = list(range(10))

# ordenado = [7.556, 10.092, 10.310, 11.348, 10.065, 9.756, 11.196, 10.260, 9.920, 9.979]
# invertido = [7.631, 8.780, 8.689, 8.111, 6.646, 9.321, 8.867, 8.837, 8.612, 8.865]
# aleat = [19.098, 19.858, 18.956, 19.592, 18.395, 20.986, 18.993, 20.642, 18.854, 19.021]

ordenado = [0.217, 0.217, 0.234, 0.217, 0.218, 0.217, 0.220, 0.217, 0.218, 0.218]
invertido = [0.696, 0.638, 0.640, 0.638, 0.641, 0.665, 0.638, 0.655, 0.638, 0.639]
aleatorio = [15.463, 15.352, 15.207, 15.256, 15.234, 15.306, 15.502, 15.174, 15.493, 15.243]

plt.plot(x, aleatorio, label='Aleatório')
plt.plot(x, invertido, label='Invertido')
plt.plot(x, ordenado, label='Ordenado')

plt.title("Tempo de execução")
plt.xlabel("Execução")
plt.ylabel("Tempo (ms)")

plt.legend()

plt.savefig('tempo.png')