In SpriteRenderer.cpp - start at line 314, end at line 315.
In Renderer3D.cpp - start at line 142, end at line 171.

Reason:
Because I am proceduraly generating sprites that are unique to a seed, I need to constintly write data to PNG files. I can no simply
reassign the m_nSpriteIndex to its current sprite because the common pointer is already in the memory. This would result in all fish being the same image.
If i tried to load the sprite at the index with a recently written image, the game engine would create a whole new texture descriptor and append it to an array.
The issue with this is that it would also add 1 to the number of texture descriptors, so after a few load/unload of fish (fish are loaded according to player position),
the game would crash because more than 1024 sprites were in the memory. 

My goal was to simply overwrite sprites instead of add more. So i implemented these changes. Now if an index in the m_pSorite array is null it will create a new sprite, but
if there is already a sprite there then it will simply pull and pass the already present texture descriptor to the function LoadTextureFile(). LoadTextureFile() will then check
if the m_nResource index is 0 (I thought this would be fine becasue fish are generated last.). if it is, it will proccess the texture normally. Otherwise it will take the
values from the passed texture descriptor  and overwrite m_pTexure at its appropriate index as well as create the shader resource at the correct index. m_nNumResourceDesc is 
not incremented. This method can create race conditions that are kindof solved by loading textures in the main program with a timed queue.