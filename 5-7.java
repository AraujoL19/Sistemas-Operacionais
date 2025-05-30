public class BancoDeDados {
    private int leitores = 0;
    private int escritores = 0;
    private int escritoresEsperando = 0;

    public synchronized void iniciarLeitura() throws InterruptedException {
        while (escritores > 0 || escritoresEsperando > 0) {
            wait();
        }
        leitores++;
    }

    public synchronized void terminarLeitura() {
        leitores--;
        if (leitores == 0) {
            notifyAll();
        }
    }

    public synchronized void iniciarEscrita() throws InterruptedException {
        escritoresEsperando++;
        while (leitores > 0 || escritores > 0) {
            wait();
        }
        escritoresEsperando--;
        escritores++;
    }

    public synchronized void terminarEscrita() {
        escritores--;
        notifyAll();
    }
}