import pygame
from cores import *
from random import shuffle



class Grafico:

    def __init__(self, screen: pygame.Surface, clock: pygame.time.Clock, fps: int, vet: list):
        self.screen = screen
        self.clock = clock
        self.fps = fps
        self.vet = vet
        self.font = pygame.font.Font(None, 60)
        self.comparacoes = 0
        self.trocas = 0

    def sort(self):
        self.comparacoes = 0
        self.trocas = 0
        self._qs(0, len(self.vet)-1)

    def exibir(self, i=None, j=None, pivo=None):
        self.screen.fill(PRETO)
        width = (self.screen.get_width() - 40) / len(self.vet) - 2
        x = 20
        down = self.screen.get_height() - 40

        for k, num in enumerate(self.vet):
            if k in [i,j]:
                cor = VERMELHO
            else:
                cor = VERDE

            pygame.draw.rect(self.screen, cor, (x, down - num, width, num))
            x += width + 2

        txt = self.font.render(f'Tamanho: {len(self.vet)}', False, BRANCO)
        self.screen.blit(txt, (20,20))

        y = 20 + txt.get_height() + 10
        txt = self.font.render(f'Comparações: {self.comparacoes}', False, BRANCO)
        self.screen.blit(txt, (20,y))
        
        y += txt.get_height() + 10
        txt = self.font.render(f'Trocas: {self.trocas}', False, BRANCO)
        self.screen.blit(txt, (20,y))

        if pivo is not None:
            pygame.draw.line(self.screen, BRANCO, (0, down-pivo), (self.screen.get_width(), down-pivo), 2)


        pygame.display.flip()
        self.clock.tick(self.fps)

    def random(self):
        shuffle(self.vet)

    def ordered(self):
        self.vet.sort()

    def inverse(self):
        self.vet.sort(reverse=True)

    def _qs(self, ini, fim):

        pivo =  self.vet[ini + (fim - ini) // 2]
        i = ini
        j = fim
        i_ordenado = True
        j_ordenado = True
        counter = 0
        
        while (i <= j):

            while (self.vet[i] < pivo):
                
                if self.vet[i] > self.vet[i+1]:
                    i_ordenado = False

                self.exibir(i, j, pivo)
                self.comparacoes += 1  
                i += 1

            while (self.vet[j] > pivo):

                if self.vet[j-1] > self.vet[j]:
                    j_ordenado = False

                self.exibir(i, j, pivo)
                self.comparacoes += 1  
                j -= 1

            counter += 1

            if i == j:
                self.exibir(i, j, pivo)
                break

            self.trocas += 1
            self.vet[i], self.vet[j] = self.vet[j], self.vet[i]
            self.exibir(i, j, pivo)

        if counter == 1 and i_ordenado and j_ordenado:
            return

        if i > ini:
            self._qs(ini, i)
        
        if i+1 < fim:
            self._qs(i+1, fim)
        
    