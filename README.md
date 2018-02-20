# TiffReader

### Premise
This is a simple proof of principle to enable writing custom tags to an OMItiff

### Dependencies
boost::gil (this is also known as the adobe image library)
libtiff (this is the underlying tiff support library that seems to be prevalent)

### Custom Tags
Reading custom tags requires no extension of the dictionary but if you wish to write them it is necessary to update the dictionary using TIFFMergeFieldInfo.

There's a really weird block in the libtiff in 
```
TIFFCleanup(TIFF *tiff)
{
...
		for (i = 0; i < tif->tif_nfields; i++) {
			TIFFField *fld = tif->tif_fields[i];
			if (fld->field_bit == FIELD_CUSTOM &&
			    strncmp("Tag ", fld->field_name, 4) == 0) {
				_TIFFfree(fld->field_name);
				_TIFFfree(fld);
			}
		}
...		
}
```
If you make the mistake of naming your custom tag "Tag JS01" for example 
it will free the field since this code get's called more than once it in 
turn triggers a segmentation fault. If you name your custom tag ANYTHING 
EXCEPT "Tag *" the program added tags work perfectly. I'm not sure why this 
block exists but I was unlucky enough to make this mistake. 

### Build tool
This application uses CMake to build. 

