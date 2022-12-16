#include "serv_cli_fifo.h"
#include "Handlers_Serv.h"


int main(){
        FILE *fp = fopen("../server_output.txt", "w");
        printf("Serveur en écoute...\n");
        fprintf(fp, "Serveur en écoute...\n");
        fflush(stdout);
        fflush(fp);
        /*Déclarations */
        char *p_fifo1 = FIFO1;
        char *p_fifo2 = FIFO2;
        int fd1, fd2;
        struct rps rep;
        struct quest qt;

        /* Création des tubes nommés */
        mkfifo(p_fifo1, 0666);
        mkfifo(p_fifo2, 0666);
        /*initialisation du générateur de nombres aléatoires*/
        srand(getpid());
        /* Ouverture des tubes nommés */
        fd1 = open(p_fifo1, O_RDWR);
        fd2 = open(p_fifo2, O_WRONLY);
        /* Installation des Handlers */
        for(int i=1; i <= NSIG; i++){
                signal(i, fin_serveur);
        }
        signal(SIGUSR1, hand_reveil);
        while(1){
                /* lecture d’une question */
                read(fd1, &qt, sizeof(qt));
                printf("Question reçu du client numero: %d\n", qt.pid);
                fprintf(fp, "Question reçu du client numero: %d\n", qt.pid);
                fflush(stdout);
                fflush(fp);
                /* construction de la réponse */
                rep.pid = getpid();
                for(int i=0; i < qt.n; i++){
                        rep.resultat[i] = rand() % NMAX + 1;
                }
                /* envoi de la réponse */
                write(fd2, &rep, sizeof(rep));
                /* envoi du signal SIGUSR1 au client concerné */
                kill(qt.pid, SIGUSR1);
        }
        return 0;
}