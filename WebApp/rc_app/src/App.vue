<template>
  <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet"/>
  <div class="container">
    <div class="row">
      <div class="col s12"><h1>eMalRob Remote Control</h1></div>
    </div>
    <div class="row">
      <div class="col s12">  
        <button class="kbc-button" v-bind:class="{ active: upArrow }" @mousedown="ButtonPressed('Up')" @click="ButtonClicked('Up')">
          <span class="material-icons">
            keyboard_arrow_up
          </span>
        </button>
        <br />
        <button class="kbc-button" v-bind:class="{ active: leftArrow }" @mousedown="ButtonPressed('Left')" @click="ButtonClicked('Left')">
          <span class="material-icons">
            keyboard_arrow_left
          </span>
        </button>
        <button class="kbc-button" v-bind:class="{ active: downArrow }" @mousedown="ButtonPressed('Down')" @click="ButtonClicked('Down')">
          <span class="material-icons">
            keyboard_arrow_down
          </span>
        </button>
        <button class="kbc-button" v-bind:class="{ active: rightArrow }" @mousedown="ButtonPressed('Right')" @click="ButtonClicked('Right')">
          <span class="material-icons">
            keyboard_arrow_right
          </span>
        </button>
      </div>
    </div>
    <div class="row valign-wrapper">
      <div class="col m3 l3"></div>

      <form class="col s12 m5 l5">   
          <div class="input-field">
            <i class="material-icons prefix">settings_ethernet</i>
            <input v-model="socket_url" id="icon_prefix" type="text" />
            <label for="icon_prefix">Websocket Adress</label>
          </div>
      </form>
      <div class="col m1 l1">
          <a v-show="!connected" class="waves-effect waves-light btn inline blue darken-1 hide-on-small-only" @click="connect()">Connect</a>
          <a v-show="connected" class="waves-effect waves-light btn inline  grey darken-1 hide-on-small-only" @click="disconnect()">Disconnect</a>
      </div>
      <div class="col m3 l3"></div>
    </div>
    <div class="row">
      <div class="col s12">
          <a v-show="!connected" class="waves-effect waves-light btn inline blue darken-1 hide-on-med-and-up" @click="connect()">Connect</a>
          <a v-show="connected" class="waves-effect waves-light btn inline  grey darken-1 hide-on-med-and-up" @click="disconnect()">Disconnect</a>
      </div>
    </div>
  </div>  
</template>



<script>
export default {
  created() {
    window.addEventListener("keydown", this.ArrowKeys);
    window.addEventListener("keyup", this.ArrowKeys);
  },
  name: "Keys",
  data() {
    
    return {
      connected: false,
      leftArrow: false,
      upArrow: false,
      rightArrow: false,
      downArrow: false,
      socket_url: "",
      ws_instance: null
    };
  },
  methods: {
    ButtonPressed(button) {
      switch (button) {
        case "Up":
            console.log("MOUSE: Up arrow pressed");
            this.ws_instance.send("U1");
          break;
        case "Left":
            console.log("MOUSE: Left arrow pressed");
            this.ws_instance.send("L1");
          break;
        case "Down":
            console.log("MOUSE: Down arrow pressed");
            this.ws_instance.send("D1");
          break;
        case "Right":
            console.log("MOUSE: Right arrow pressed");
            this.ws_instance.send("R1");
          break;
      }
    },
    ButtonClicked(button) {
      switch (button) {
        case "Up":
            console.log("MOUSE: Up arrow released");
            this.ws_instance.send("U0");
          break;
        case "Left":
            console.log("MOUSE: Left arrow released");
            this.ws_instance.send("L0");
          break;
        case "Down":
            console.log("MOUSE: Down arrow released");
            this.ws_instance.send("D0");
          break;
        case "Right":
            console.log("MOUSE: Right arrow released");
            this.ws_instance.send("R0");
          break;
      }
    },
    ArrowKeys(event) {
      switch (event.key) {
        case "ArrowUp":
            if (event.type == "keydown" && this.upArrow != true) {
              console.log("KEYBOARD: Up arrow pressed");
              this.ws_instance.send("U1");
              this.upArrow = true;
            } else if (event.type == "keyup" && this.upArrow == true) {
              console.log("KEYBOARD: Up arrow released");
              this.ws_instance.send("U0");
              this.upArrow = false;
            }
          break;
        case "ArrowLeft":
            if (event.type == "keydown" && this.leftArrow != true) {
              console.log("KEYBOARD: Left arrow pressed");
              this.ws_instance.send("L1");
              this.leftArrow = true;
            } else if (event.type == "keyup" && this.leftArrow == true) {
              console.log("KEYBOARD: Left arrow released");
              this.ws_instance.send("L0");
              this.leftArrow = false;
            }
          break;
        case "ArrowDown":
            if (event.type == "keydown" && this.downArrow != true) {
              console.log("KEYBOARD: Down arrow pressed");
              this.ws_instance.send("D1");
              this.downArrow = true;
            } else if (event.type == "keyup" && this.downArrow == true) {
              console.log("KEYBOARD: Down arrow released");
              this.ws_instance.send("D0");
              this.downArrow = false;
            }
          break;
        case "ArrowRight":
            if (event.type == "keydown" && this.rightArrow != true) {
              console.log("KEYBOARD: Right arrow pressed");
              this.ws_instance.send("R1");
              this.rightArrow = true;
            } else if (event.type == "keyup" && this.rightArrow == true) {
              console.log("KEYBOARD: Right arrow released");
              this.ws_instance.send("R0");
              this.rightArrow = false;
            }
          break;
      }
    },
    connect() {
      console.log("Connecting ...")
      this.ws_instance = new WebSocket(this.socket_url)
      this.ws_instance.onmessage = function(msg) {
        console.log(msg);
      }
      this.ws_instance.onopen = function(msg) {
        console.log(msg)  
        console.log("Successfully connected to websocket server...")
      }
      this.connected = true;
    },
    disconnect() {
      
      this.ws_instance.close();
      this.ws_instance.onclose = function(msg) {
        console.log(msg)
        console.log("Successfully disconnected from websocket server...")
      }
      this.connected = false;
    }
  }
};
</script>

<style lang="scss">
$primary-color: color("materialize-red", "lighten-2") !default;
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
.active {
  color: #000 !important;
}
input[type="text"]:focus {
  border-bottom: 1px solid #000 !important;
  box-shadow: 0 1px 0 0 #000 !important;
}
</style>
