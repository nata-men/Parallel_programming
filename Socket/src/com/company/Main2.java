package com.company;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.util.Random;

import static java.lang.Math.abs;

public class Main2 {
    private static final String IP = "127.0.0.1";
    private static final int PORT = 6000;

    public static void main(String[] args){
        Main2.work(IP, PORT);
    }

    private static void work(String ip, int port){
        try {
            Socket conn = new Socket(ip, port);

            System.out.println(
                    String.format(
                            "Connected to %s",
                            conn.getRemoteSocketAddress().toString()
                    ));


            InputStream sin = conn.getInputStream();
            OutputStream sout = conn.getOutputStream();

            int numberToSend = new Random().nextInt(1000);

            byte[] outBuffer = ByteBuffer.allocate(4).putInt(numberToSend).array();
            sout.write(outBuffer);

            System.out.println(
                    String.format(
                            "Send [%s] to %s",
                            numberToSend,
                            conn.getRemoteSocketAddress().toString()
                    ));

            byte[] data = new byte[8];
            sin.read(data);
            long number = ByteBuffer.wrap(data).getLong();

            System.out.println(
                    String.format(
                            "Received [%s] from %s",
                            number,
                            conn.getRemoteSocketAddress().toString()
                    ));

        } catch(Exception x) {
            x.printStackTrace();
        }
    }
}
