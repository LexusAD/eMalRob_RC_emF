import { createApp } from "vue";
import App from "./App.vue";
import "keyboard-css";
import "materialize-css";
import "materialize-css/dist/css/materialize.min.css";
import socketio from 'socket.io';
import VueSocketIO from 'vue-socket.io';


createApp(App).mount("#app");
