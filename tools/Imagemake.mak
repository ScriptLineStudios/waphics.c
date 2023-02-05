image_loader: tools/image_loader.c
	gcc -o image_loader tools/image_loader.c -lm
	
	./image_loader assets/grass.png grass
	./image_loader assets/ScriptLine.png sl

	rm image_loader

clean:
	rm image_loader