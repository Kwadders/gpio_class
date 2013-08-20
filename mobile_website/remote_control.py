#!/usr/bin/env python

"""
Simple example to show how to use cherrypy with jquery and jquery mobile.
"""

import cherrypy
import RPi.GPIO as GPIO
import os

class HelloWorld:
    """ Sample request handler class. """
    print "****test****"

    @cherrypy.expose
    def index(self):
        return '''<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1, user-scalable=0;" />
        <meta name="viewport" content="width=device-width"/>
        <meta name="apple-mobile-web-app-capable" content="yes" />
        <title>
        </title>
        <link rel="stylesheet" href="static/jquery.mobile-1.0.1.min.css" />
        <style>
            /* App custom styles */
        </style>
        <script src="static/jquery.min.js">
        </script>
        <script src="static/jquery.mobile-1.0.1.min.js">
        </script>
        <script type="text/javascript">
        $(document).ready(function() {
            //stop the page from doing a stretch from the top when dragged ;
            document.ontouchmove = function(event){ event.preventDefault(); };
            //move beyond the address  bar to hide ;
            window.scrollTo(0, 1);
            //start button click code;
            $("#start").click(function () {$.post('/request',{key_pressed:"start"})});
            $("#enter").click(function () {$.post('/request',{key_pressed:"enter"})});
            $("#esc").click(function () {$.post('/request',{key_pressed:"esc"})});
            $("#power").change(function () {$.post('/request',{key_pressed:"power_"+$(this).val()})});
        });
        </script>
    </head>
    <body style="overflow: hidden;overflow-x:hidden;">
        <div data-role="page" data-theme="a" id="page1">
            <div data-theme="a" data-role="header" data-position="">
                <h5>
                    Web Remote
                </h5>
            </div>
            <div data-role="content">
                <div class="ui-grid-b">
                    <div class="ui-block-a">
                        <button type="button" id="start" data-role="button" data-transition="fade" >
                            Start
                        </button>
                    </div>
                    <div class="ui-block-b">
                        <button type="button" id="enter" data-role="button" data-transition="fade">
                            Enter
                        </button>
                    </div>
                    <div class="ui-block-c">
                        <button type="button" id="esc" data-role="button" data-transition="fade">
                            Esc
                        </button>
                    </div>
                    <div class="ui-block-a">

                </div>
                <div data-role="fieldcontain">
                    <fieldset data-role="controlgroup">
                        <label for="power">
                        </label>
                        <select name="power" id="power" data-theme="a" data-role="slider">
                            <option value="off">
                                Off
                            </option>
                            <option value="on">
                                On
                            </option>
                        </select>
                    </fieldset>
                </div>
            </div>
        </div>
        <script>
            //App custom javascript
        </script>
    </body>
</html>
'''
    @cherrypy.expose
    def request(self, **data):
        # Then to access the data do the following
        #print data
        key = data['key_pressed'].lower()
        if key == "start":
            print "start"
	    os.system("cd ../../..")
            os.system('gpio_control')	       
        elif key == "enter":
            print "enter"
        elif key == "power_on":
            print "on"
        elif key == "esc":
            print "esc"
        elif key == "power_off":
            print "off"
        else:
            print key

# bind to all IPv4 interfaces
#cherrypy.config.update({'server.socket_host': '10.146.146.146'})
#cherrypy.quickstart(HelloWorld())
            
import os.path
tutconf = os.path.join(os.path.dirname(__file__), 'tutorial.conf')

if __name__ == '__main__':
    # CherryPy always starts with app.root when trying to map request URIs
    # to objects, so we need to mount a request handler root. A request
    # to '/' will be mapped to HelloWorld().index().
    cherrypy.quickstart(HelloWorld(), config=tutconf)
else:
    # This branch is for the test suite; you can ignore it.
    cherrypy.tree.mount(HelloWorld(), config=tutconf)
