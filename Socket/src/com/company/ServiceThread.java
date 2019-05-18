package com.company;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.nio.ByteBuffer;

public class ServiceThread extends Thread {

    private Socket socketToServe;

    ServiceThread(Socket socketToServe){
        super();
        this.socketToServe = socketToServe;
    }

    @Override
    public void run() {
        System.out.println(
                String.format(
                        "Accepted connection from %s",
                        this.socketToServe.getRemoteSocketAddress().toString()
        ));

        try {
            InputStream sin = this.socketToServe.getInputStream();
            OutputStream sout = this.socketToServe.getOutputStream();

            byte[] inData = new byte[4];
            sin.read(inData);
            int inNumber = ByteBuffer.wrap(inData).getInt();

            System.out.println(
                    String.format(
                            "Received [%s] from %s",
                            inNumber,
                            this.socketToServe.getRemoteSocketAddress().toString()
                    ));

            long result = this.mySquare(inNumber);

            byte[] outBuffer = ByteBuffer.allocate(8).putLong(result).array();
            sout.write(outBuffer);

            System.out.println(
                    String.format(
                            "Send [%s] to %s",
                            result,
                            this.socketToServe.getRemoteSocketAddress().toString()
                    ));

        } catch(Exception x) {
            x.printStackTrace();
        }
    }

    private long mySquare(int n) {
        long result = n*n;
        return result;


    }

}

