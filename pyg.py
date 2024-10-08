import pygame
from grafico import Grafico
from cores import *


pygame.init()

screen = pygame.display.set_mode((0,0), pygame.FULLSCREEN)
clock = pygame.time.Clock()

velocidade = 60
numeros = [n for n in range(7, 700, 14)]

grafico = Grafico(
    screen=screen,
    clock=clock,
    fps=velocidade,
    vet=numeros
    )

fps = 60
rodando = True
while rodando:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            rodando = False
            break
        elif event.type == pygame.KEYDOWN:
        
            if event.key == pygame.K_r:
                grafico.random()

            elif event.key == pygame.K_i:
                grafico.inverse()

            elif event.key == pygame.K_o:
                grafico.ordered()

            elif event.key == pygame.K_SPACE:
                grafico.comparacoes = 0
                grafico.trocas = 0

            elif event.key == pygame.K_q:
                grafico.sort()


    screen.fill(PRETO)

    grafico.exibir()

    clock.tick(fps)
    pygame.display.flip()