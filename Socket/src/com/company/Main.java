package com.company;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class Main {
    private static final int PORT=6000;

    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(PORT);
            System.out.println(
                    String.format(
                            "Server started at %s",
                            serverSocket.getLocalSocketAddress().toString()
                    )
            );

            while (true) {
                Socket clientSocket = serverSocket.accept();
                System.out.println(
                    String.format(
                            "Accepted connection from %s",
                            clientSocket.getRemoteSocketAddress().toString()
                            )
                );

                new ServiceThread(clientSocket).start();
            }
        }
        catch (IOException e){
            System.out.println(e.toString());
        }
    }
}
