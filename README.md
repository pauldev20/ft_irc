<div align="center">
    <img src="https://em-content.zobj.net/source/apple/391/globe-with-meridians_1f310.png" align="center" width=180 height=180/>
    <h1>ft_irc Project</h1>
    <p align="center">
        <a href="#question-about-this-project">About This Project</a>
        ·
        <a href="#hammer_and_wrench-how-its-made">How It's Made</a>
        ·
        <a href="#computer-usage">Usage</a>
    </p>
    <br/>
</div>
<br/>

# :question: About This Project
The **ft_irc** project is part of the 42 school curriculum. It involves building an IRC (Internet Relay Chat) server that follows the RFC1459 specifications. The server is capable of handling multiple clients and supporting a wide range of IRC commands, while being extensible to include bots and other features.

The project demonstrates proficiency in network programming, concurrency, and communication protocols, all while maintaining efficient resource management and handling.

**The project is split into multiple parts**:
- **Server**: Implements the core IRC server functionality.
- **Client**: Handles client-server communication and interaction with various IRC commands.
- **Commands**: Implements the various commands supported by the server such as JOIN, PART, PRIVMSG, NICK, etc.
- **Bot**: Contains an IRC bot that interacts with the server and performs automated tasks.

# :hammer_and_wrench: How It's Made
**Networking**: The project makes extensive use of sockets to implement communication between the server and multiple clients.

**Concurrency**: The server is designed to handle multiple connections simultaneously, processing requests in parallel while maintaining thread safety.

**Command Execution**: Each supported IRC command is implemented as a separate function, which can be executed based on the input received from the clients.

**Bot Integration**: The project includes a simple IRC bot capable of responding to commands and automating interactions within the chat.

**Makefile**: A `Makefile` is provided to compile and build the project with all necessary flags and dependencies.

# :computer: Usage
To compile and run the server, follow these steps:

1. Navigate to the project directory in your terminal:
   ```
   cd /path/to/ft_irc
   ```

2. Compile the project using the `Makefile`:
   ```
   make
   ```

3. Run the server with the following command:
   ```
   ./ircserv <port> <password>
   - `<port>`: The port number the server will listen on.
   - `<password>`: The password required to join the server.
   ```

4. Connect a client to the server using an IRC client (e.g., `irssi`, `weechat`, etc.):
   ```
   /connect <hostname> <port> <password>
   ```
Once connected, you can execute various IRC commands like JOIN, PRIVMSG, NICK, and others.

To compile and run the bot, follow these steps:

1. Navigate to the project directory in your terminal:
   ```
   cd /path/to/ft_irc
   ```

2. Compile the project using the `Makefile`:
   ```
   make
   ```

3. Connect the bot to a server:
   ```
   ./ircbot <port> <password> <nick>
   - `<port>`: The port number of the server.
   - `<password>`: The password required to join the server.
   - `<nick>`: The nickname of the bot.
   ```
