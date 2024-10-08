import pygame
from random import shuffle


PRETO = (0,0,0)
VERDE = (0,255,0)
VERMELHO = (255,0,0)
AQUA = (0,255,255)

pygame.init()
screen = pygame.display.set_mode((0,0), pygame.FULLSCREEN)




class Grafico:

    def __init__(self, screen, clock, fps, vet):
        self.screen = screen
        self.clock = clock
        self.fps = fps
        self.vet = vet

    def sort(self):
        self.comparacoes = 0
        self.trocas = 0
        self._qs(0, len(self.vet)-1)

    def exibir(self, i=None, j=None, pivo_index=None):
        screen.fill(PRETO)
        width = (self.screen.get_width() - 8*(len(self.vet))) / len(self.vet)
        x = 20
        down = self.screen.get_height() - 20

        for k, num in enumerate(self.vet):
            if k in [i,j]:
                cor = VERMELHO
            elif k == pivo_index:
                cor = AQUA
            else:
                cor = VERDE
            pygame.draw.rect(self.screen, cor, (x, down - 20 - num, width, num))
            x += width + 2
        
        pygame.display.flip()
        self.clock.tick(self.fps)

    def random(self):
        shuffle(self.vet)

    def _qs(self, ini, fim):

        pivo_index = ini + (fim - ini) // 2
        pivo =  self.vet[pivo_index]

        i = ini
        j = fim

        while True:

            while (self.vet[i] < pivo):
                self.exibir(i,j, pivo_index)
                self.comparacoes += 1
                i += 1
            
            while (self.vet[j] > pivo):
                self.exibir(i,j, pivo_index)
                self.comparacoes += 1
                j -= 1
            
            if i >= j:
                break

            self.vet[i], self.vet[j] = self.vet[j], self.vet[i]
            self.trocas += 1

            self.exibir(i,j)


        if i > ini:
            self._qs(ini, i)
        if i+1 < fim:
            self._qs(i+1, fim)
        

clock = pygame.time.Clock()
g = Grafico(screen, clock, 1, [n for n in range(10, 700, 50)])

fps = 60
rodando = True
while rodando:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            rodando = False
            break
        elif event.type == pygame.KEYDOWN:
        
            if event.key == pygame.K_r:
                g.random()
                print(g.vet)

            elif event.key == pygame.K_q:
                g.sort()
                print(g.vet)

    screen.fill(PRETO)

    g.exibir()

    clock.tick(fps)
    pygame.display.flip()