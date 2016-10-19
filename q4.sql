DROP TABLE IF EXISTS bounded_by_rect;
CREATE TABLE bounded_by_rect AS 
    SELECT  id 
    FROM projected_poi ppoi
    WHERE minX >= ?
      AND maxX <= ?
      AND maxY >= ?
      AND minY <= ?;

SELECT id 
FROM bounded_by_rect bbr, poi_tag pt
WHERE bbr.id = poi_tag.id
  AND key = "class"
  AND value = ?;