#include "serv_cli_fifo.h"
#include "Handlers_Cli.h"
int main(){
    /* Déclarations */
    char *p_fifo1 = FIFO1;
    char *p_fifo2 = FIFO2;
    int fd1, fd2;
    struct rps rep;
    struct quest qt;
    /* Ouverture des tubes nommés */
    fd1 = open(p_fifo1, O_WRONLY);
    fd2 = open(p_fifo2, O_RDONLY);
    /* Installation des Handlers */
    signal(SIGUSR1, hand_reveil);
    /* Construction et envoi d’une question */
    qt.pid = getpid();
    srand(getpid());
    qt.n = rand() % NMAX + 1;
    write(fd1, &qt, sizeof(qt));
    /* Attente de la réponse */
    pause();
    /* Lecture de la réponse */
    read(fd2, &rep, sizeof(rep));
    /* Envoi du signal SIGUSR1 au serveur */
    kill(rep.pid, SIGUSR1);
    /* Traitement local de la réponse */    
    printf("Il y'a %d Numeros au total: \n", qt.n);
    printf("Ces nombres sont comme suit: \n");
    for(int i=0; i < qt.n; i++){
        printf("%d    ", rep.resultat[i]);
    }
    fflush(stdout);
    return 0;    
}
