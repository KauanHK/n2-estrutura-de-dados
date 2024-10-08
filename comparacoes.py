import matplotlib.pyplot as plt


x = list(range(10))

ordenado = [49999]*10
invertido = [99997]*10
aleat = [1063213, 1008343, 969176, 965532, 972555, 980836, 1026032, 987022, 939073, 988415]

for lista in [ordenado, invertido, aleat]:
    for i in range(len(lista)):
        lista[i] /= 1000

plt.plot(x, ordenado, label='Ordenado')
plt.plot(x, invertido, label='Invertido')
plt.plot(x, aleat, label='Aleatório')

plt.title("Comparações")
plt.xlabel("Execução")
plt.ylabel("Comparações (Milhares)")

plt.text(5, 15, '49999 comparações', fontsize=10, color='black', ha='center')
plt.text(5, 120, '99997 comparações', fontsize=10, color='black', ha='center')

plt.legend()


plt.savefig('comparacoes.png')