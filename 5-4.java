public class Fila {
    private final Queue<Integer> fila = new LinkedList<>();

    public synchronized void adicionar(int item) {
        fila.add(item);
        notifyAll();
    }

    public synchronized int remover() throws InterruptedException {
        while (fila.isEmpty()) {
            wait();
        }
        return fila.poll();
    }
}

//starvation ocorre porque notify() acorda apenas uma thread aleatória, e as outras podem nunca mais ser escolhidas
