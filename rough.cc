class IOContxt {
  public:
    IOContext();

    /* stops and joins with the thread if it's still running */
    ~IOContext();

    /* starts the internal thread */
    void start();

    /* requests the internal thread to stop (without waiting for it) */
    void stop();

    /* joins with the internal thread */
    void join();

    /* implicit conversion to the primtive type */
    operator boost::io_context& ();
}

class Socket {
  public:
    /* This adopts a connected socket created by a tcp acceptor */
    Socket(boost::ip::tcp::socket&& _connected_socket);

    /* This creates a disconnected socket that can be connected actively */
    Socket(IOContext& _io_context);

    /* Attempts to connect at the address _host and port _service */
    void async_connect(std::string_view const& _host, std::string_view const& _service);

    /* Asynchronously sends a packet */
    void async_send_packet(Packet const& _packet);

    /* Returns the buffer containing all received packets, and clears the buffer */
    std::vector<Packet> get_received_packets()'
};

class Acceptor {
public:
    Acceptor(IOContext& _io_context);

    /* Initialises accepting new connections */
    void start();

    /* Returns the sockets accepted so far */
    std::vector_or_something_else<Socket> get_accepted_sockets();

private:
    /* Called for the first time in start(), and subsequently, called by the callback passed to boost::ip::tcp::acceptor::async_accept() */
    void async_accept();

};
