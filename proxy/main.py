import sys
sys.path.append("libtpproto-py")
sys.path.append("libtpclient-py")

import tp.client.threads as tpthread
import tp.client.cache as tpcache

import cache
import server
import starmap

def pickle_dump(target_object, name="pickle"):
    import pickle
    try:
        f = open("%s_dump" % name, 'w')
        pickle.dump(target_object, f)
    except pickle.PicklingError, e:
        print "Pickle Error:", e
    finally:
        f.close()

class GUI(object):
    def __init__(self, application):
        self.application = application
        self.connected = False

    def ConfigLoad(self, config):
        pass
    
    def Call(self, method, *args, **kw):
        """Call a method in this thread"""
        method(*args, **kw)

    def Post(self, event):
        """Post an Event into the current window"""
        #print socket.send("%s %s" % (event.__class__, json.dumps(evt.__dict__)))

    def Cleanup(self):
        self.application.Exit()
        self.application.finder.remote.exit()

    def start(self):
        print "connecting"
        self.application.network.Call(self.connect, "192.168.1.115", "jmtan", "123", True)
        while not self.connected:
            pass

    def connect(self, host, username, password, debug=True):
        def connect_callback(*args, **kw):
            print "connection callback", args, kw

        def cache_callback(*args, **kw):
            print "cache callback", args, kw

        if self.application.network.ConnectTo(host, username, password, debug, connect_callback):
            self.application.network.CacheUpdate(cache_callback)
            self.application.cache.CacheUpdateEvent(None)
            print "connection success, now serving content"

            app_cache = self.application.cache
            #pickle_dump(cache.objects, "object")
            #pickle_dump(cache.designs, "design")
            #pickle_dump(cache.messages, "message")
            #pickle_dump(cache.players, "player")
            #pickle_dump(cache.resources, "resource")
            server.ZMQServer(cache.EntityCache(app_cache, starmap.Map())).serve("tcp://127.0.0.1:5555")

class TPApplication(tpthread.Application):
    GUIClass = GUI
    NetworkClass = tpthread.NetworkThread
    MediaClass = tpthread.MediaThread
    FinderClass = tpthread.FinderThread
    ConfigFile = "pyogre_preferences"

if __name__ == "__main__":
    app = TPApplication()
    app.Run();
