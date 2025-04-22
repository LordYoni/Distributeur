import express from 'express';
import { createServer } from 'node:http';
import { fileURLToPath } from 'node:url';
import { dirname, join } from 'node:path';
import { Server } from 'socket.io';
import { SerialPort } from 'serialport'

// Create a port
const port = new SerialPort({
  path: 'COM4',
  baudRate: 9600
})

// Open errors will be emitted as an error event
port.on('error', function(err) {
  console.log('Error: ', err.message)
})

const app = express();
const server = createServer(app);
const io = new Server(server);

const __dirname = dirname(fileURLToPath(import.meta.url));



app.use('/webapp', express.static(join(__dirname, 'WebApp')));
app.use('/adminapp', express.static(join(__dirname, 'AdminApp')));



io.on('connection', (socket) => {
  console.log('Yoni s\'est connecté');

  socket.on('cardSelected', (msg) => {

    port.write(msg, err => {
      if(err)
        console.log('Error ' + err.message);
    });
  });

  socket.on('disconnect', () => {
    console.log('Yoni s\'est déconnecté');
  });
});





server.listen(3000, () => {
  console.log('server running at http://localhost:3000');
});