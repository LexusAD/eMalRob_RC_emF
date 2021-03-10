<template>
  <div class="container">
    <div class="row">
      <form class="col s12 m8 l8 xl8">
        <div class="row">
          <div class="input-field col s12 m9 l6 xl6 offset-xl5 offset-l5 offset-m2">
            <i class="material-icons prefix">settings_ethernet</i>
            <input v-model="socket_adress" id="icon_prefix" type="text" />
            <label for="icon_prefix">Websocket Adress</label>
          </div>
          <div class="input-field col s1 m1 l1 xl1">
            <a v-on:click="connect" class="waves-effect waves-light btn inline blue darken-1">Connect</a>
          </div>
        </div>
      </form>
    </div>
  </div>
</template>

<script>
export default {
  name: "Forms",
  data() {
    return {
      socket_adress: "",
    };
  },
  methods: {
    connect() {
      console.log(this.socket_adress);
    },
  },
};
</script>

<style lang="sass"></style>
