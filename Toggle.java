import java.io.*;
import java.net.*;

public class Toggle {
    public static void main(String[] args) throws IOException, InterruptedException {
        if(args.length > 0) {
            Thread.sleep((int)(Double.parseDouble(args[0]) * 3.6E6));
        }
        Socket socket = new Socket ("192.168.1.9", 3300);
        PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
        out.println("T");
        out.close();
        socket.close();
    }
}
