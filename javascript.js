function _render(instance, ctx, func) { image = get_image(instance, instance.exports.run()); ctx.putImageData(image, 0, 0); window.requestAnimationFrame(func); } (async () => { function render() { _render(instance, ctx, render); } current_key = null; function jfloor(x) { return Math.floor(x); } function jsqrt(x) { return Math.sqrt(x); } function jabs(x) { return Math.abs(x); } function jprint(x) { console.log(x); } function jsin(x) { return Math.sin(x); } var keyCode; function get_key(key) { document.addEventListener( "keydown", function(event) { keyCode = event.keyCode; }, ); document.addEventListener( "keyup", function(event) { if (event.keyCode == keyCode) keyCode = null; }, ); if (keyCode == key) return 1; return 0; } function play_sound(path) { var size = 1; var array = new Uint8Array(buffer, path, size); while (array[array.length - 1] != 0) { size++; array = new Uint8Array(buffer, path, size); } array = new Uint8Array(buffer, path, size-1); const decoder = new TextDecoder(); const string = decoder.decode(array); var audio = new Audio(string); audio.play(); } var c = document.getElementById("canvas" ,{"alpha": false}); var ctx = c.getContext("2d"); const w = await WebAssembly.instantiateStreaming(fetch("output.wasm"), {"env": {"jsin": jsin, "play_sound": play_sound, "jfloor": jfloor, "jprint": jprint, "jsqrt": jsqrt, "jabs": jabs, "get_key": get_key}}); const buffer = w.instance.exports.memory.buffer; const instance = w.instance; instance.exports.init(); window.requestAnimationFrame(render); })();