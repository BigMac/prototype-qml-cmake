#ifndef RESOURCEREPOSITORYFSMEVENTS_H
#define RESOURCEREPOSITORYFSMEVENTS_H

class CommonConnection;

struct Connected
{
    Connected(CommonConnection& connection) : connection(connection) {}
    CommonConnection& connection;
};

struct ConnectionError
{
};

#endif // RESOURCEREPOSITORYFSMEVENTS_H
