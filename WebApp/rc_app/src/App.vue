<template>
  <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet"/>
  <div class="container">
    <div class="row">
      <div class="col s12"><h1>eMalRob Remote Control</h1></div>
    </div>
    <div class="row">
      <div class="col s12">  
        <button class="kbc-button" v-bind:class="{ active: upArrow }" @click="ButtonClick('Up')">
          <span class="material-icons">
            keyboard_arrow_up
          </span>
        </button>
        <br />
        <button class="kbc-button" v-bind:class="{ active: leftArrow }" @click="ButtonClick('Left')">
          <span class="material-icons">
            keyboard_arrow_left
          </span>
        </button>
        <button class="kbc-button" v-bind:class="{ active: downArrow }" @click="ButtonClick('Down')">
          <span class="material-icons">
            keyboard_arrow_down
          </span>
        </button>
        <button class="kbc-button" v-bind:class="{ active: rightArrow }" @click="ButtonClick('Right')">
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
          <a v-on:click="connect" class="waves-effect waves-light btn inline blue darken-1 hide-on-small-only">Connect</a>
      </div>
      <div class="col m3 l3"></div>
    </div>
    <div class="row">
      <div class="col s12">
          <a v-on:click="connect" class="waves-effect waves-light btn inline blue darken-1 hide-on-med-and-up">Connect</a>
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
      leftArrow: false,
      upArrow: false,
      rightArrow: false,
      downArrow: false,
      socket_url: "",
      ws_instance: null
    };
  },
  methods: {
    ButtonClick(button) {
      console.log(button);
    },
    ArrowKeys(event) {
      switch (event.key) {
        case "Up":
        case "ArrowUp":
            if (event.type == "keydown" && this.upArrow != true) {
              console.log("Up Arrow Down");
              this.upArrow = true;
            } else if (event.type == "keyup" && this.upArrow == true) {
              console.log("Up Arrow Released");
              this.upArrow = false;
            }
          break;
        case "Left":
        case "ArrowLeft":
            if (event.type == "keydown" && this.leftArrow != true) {
              console.log("left Arrow Down");
              this.leftArrow = true;
            } else if (event.type == "keyup" && this.leftArrow == true) {
              console.log("left Arrow Released");
              this.leftArrow = false;
            }
          break;
        case "Down":
        case "ArrowDown":
            if (event.type == "keydown" && this.downArrow != true) {
              console.log("down Arrow Down");
              this.downArrow = true;
            } else if (event.type == "keyup" && this.downArrow == true) {
              console.log("down Arrow Released");
              this.downArrow = false;
            }
          break;
        case "Right":
        case "ArrowRight":
            if (event.type == "keydown" && this.rightArrow != true) {
              console.log("right Arrow Down");
              this.rightArrow = true;
            } else if (event.type == "keyup" && this.rightArrow == true) {
              console.log("right Arrow Released");
              this.rightArrow = false;
            }
          break;
      }
    },
    connect() {
      console.log("Connecting ...")
      this.ws_instance = new WebSocket(this.socket_url)
      
      this.ws_instance.onmessage = function(event) {
        console.log(event);
      }

      this.ws_instance.onopen = function(event) {
        console.log(event)
        console.log("Successfully connected to the echo websocket server...")
      }
    },
    sendKey(key, state) {
      console.log(this.ws_instance);
      this.ws_instance.send(message);
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
