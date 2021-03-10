<template>
  <link
    href="https://fonts.googleapis.com/icon?family=Material+Icons"
    rel="stylesheet"
  />
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
  <br /><br /><br />
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
      downArrow: false
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
          if (event.type == "keydown") {
            this.upArrow = true;
          } else {
            this.upArrow = !this.upArrow;
          }
          break;
        case "Left":
        case "ArrowLeft":
          if (event.type == "keydown") {
            this.leftArrow = true;
          } else {
            this.leftArrow = !this.leftArrow;
          }
          break;
        case "Down":
        case "ArrowDown":
          if (event.type == "keydown") {
            this.downArrow = true;
          } else {
            this.downArrow = !this.downArrow;
          }
          break;
        case "Right":
        case "ArrowRight":
          if (event.type == "keydown") {
            this.rightArrow = true;
          } else {
            this.rightArrow = !this.rightArrow;
          }
          break;
      }
    }
  }
};
</script>

<style lang="sass"></style>
