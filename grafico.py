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

            if self.vet[k-1] > self.vet[k]:
                cor = AQUA

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

        pivo_index = ini + (fim - ini) // 2
        pivo =  self.vet[pivo_index]

        i = ini
        j = fim
        counter = 0

        while True:

            while (self.vet[i] < pivo):
                # self.exibir(i,j, pivo)
                self.comparacoes += 1
                i += 1
            
            while (self.vet[j] > pivo):
                # self.exibir(i,j, pivo)
                self.comparacoes += 1
                j -= 1

            if i == j:
                if counter == 0 and fim - ini > 5:
                    return
                break
                
            counter += 1

            if i >= j:
                break
            
            # self.exibir(i,j, pivo)

            self.vet[i], self.vet[j] = self.vet[j], self.vet[i]
            self.trocas += 1


            # self.exibir(i,j, pivo)

        if i > ini:
            self._qs(ini, i)
        if i+1 < fim:
            self._qs(i+1, fim)