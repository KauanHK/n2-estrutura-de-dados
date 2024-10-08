import pygame
from grafico import Grafico
from cores import *


pygame.init()

screen = pygame.display.set_mode((0,0), pygame.FULLSCREEN)
clock = pygame.time.Clock()

velocidade = 15
numeros = [n for n in range(7, 700, 14)]

grafico = Grafico(
    screen=screen,
    clock=clock,
    fps=velocidade,
    vet=numeros
    )

font = pygame.font.Font(None, 120)
show_fps = False

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

            elif event.key == pygame.K_UP:
                grafico.fps += 1 if grafico.fps < 60 else 0

            elif event.key == pygame.K_DOWN:
                grafico.fps -= 1 if grafico.fps > 1 else 0

            elif event.key == pygame.K_f:
                show_fps = not show_fps


    screen.fill(PRETO)

        
    grafico.exibir()

    if show_fps:
        txt = font.render(str(grafico.fps), False, BRANCO, PRETO)
        screen.blit(txt, screen.get_rect().center)

    clock.tick(fps)
    pygame.display.flip()