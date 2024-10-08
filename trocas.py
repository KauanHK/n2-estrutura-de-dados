import matplotlib.pyplot as plt



x = list(range(10))

ordenado = [0]*10
invertido = [25000]*10
aleat = [209781, 208213, 207868, 211486, 210125, 208709, 209844, 211244, 210259, 210066]

for lista in [ordenado, invertido, aleat]:
    for i in range(len(lista)):
        lista[i] /= 1000

plt.plot(x, ordenado, label='Ordenado')
plt.plot(x, invertido, label='Invertido')
plt.plot(x, aleat, label='Aleatório')

plt.title("Número de Trocas para um vetor de 50000 números")
plt.xlabel("Execução")
plt.ylabel("Trocas (Milhares)")

txt = "Nenhuma troca para vetor já ordenado"
plt.text(5, 10, txt, fontsize=10, color='black', ha='center')

txt = "25 mil trocas para vetor invertido"
plt.text(5, 40, txt, fontsize=10, color='black', ha='center')

txt = "Valores muito próximos para "\
      "um vetor de números aleatórios.\n"\
     f"Variou entre {min(aleat)} e {max(aleat)}"

plt.text(5, 180, txt, fontsize=10, color='black', ha='center')

plt.legend()

plt.savefig('trocas.png')